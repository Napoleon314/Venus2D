////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBoundingTree.cpp
//  Version:     v1.00
//  Created:     29/1/2015 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeBoundingTree.inl"
#endif

#define NULL_NODE (-1)
#define BOX_EXT (0.1f)
#define BOX_MUL (2.0f)

//--------------------------------------------------------------------------
VeBoundingTree2D::VeBoundingTree2D()
{
	m_i32Root = NULL_NODE;

	m_i32NodeCapacity = 16;
	m_i32NodeCount = 0;
	m_pkNodes = (Node*)VeMalloc(m_i32NodeCapacity * sizeof(Node));
	VeZeroMemory(m_pkNodes, m_i32NodeCapacity * sizeof(Node));

	for(VeInt32 i(0); i < m_i32NodeCapacity - 1; ++i)
	{
		m_pkNodes[i].m_i32Next = i + 1;
		m_pkNodes[i].m_i32Height = -1;
	}
	m_pkNodes[m_i32NodeCapacity - 1].m_i32Next = NULL_NODE;
	m_pkNodes[m_i32NodeCapacity - 1].m_i32Height = -1;
	m_i32FreeList = 0;

	m_u32Path = 0;

	m_i32InsertionCount = 0;
}
//--------------------------------------------------------------------------
VeBoundingTree2D::~VeBoundingTree2D()
{
	VeFree(m_pkNodes);
}
//--------------------------------------------------------------------------
VeInt32 VeBoundingTree2D::AllocateNode()
{
	if (m_i32FreeList == NULL_NODE)
	{
		VE_ASSERT(m_i32NodeCount == m_i32NodeCapacity);
		m_i32NodeCapacity *= 2;
		m_pkNodes = (Node*)VeRealloc(m_pkNodes, m_i32NodeCapacity * sizeof(Node));

		for(VeInt32 i = m_i32NodeCount; i < m_i32NodeCapacity - 1; ++i)
		{
			m_pkNodes[i].m_i32Next = i + 1;
			m_pkNodes[i].m_i32Height = -1;
		}
		m_pkNodes[m_i32NodeCapacity - 1].m_i32Next = NULL_NODE;
		m_pkNodes[m_i32NodeCapacity - 1].m_i32Height = -1;
		m_i32FreeList = m_i32NodeCount;
	}

	VeInt32 i32Node = m_i32FreeList;
	m_i32FreeList = m_pkNodes[i32Node].m_i32Next;
	m_pkNodes[i32Node].m_i32Parent = NULL_NODE;
	m_pkNodes[i32Node].m_i32Child0 = NULL_NODE;
	m_pkNodes[i32Node].m_i32Child1 = NULL_NODE;
	m_pkNodes[i32Node].m_i32Height = 0;
	m_pkNodes[i32Node].m_pvUserData = NULL;
	++m_i32NodeCount;
	return i32Node;
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::FreeNode(VeInt32 i32Node)
{
	VE_ASSERT(0 <= i32Node && i32Node < m_i32NodeCapacity);
	VE_ASSERT(0 < m_i32NodeCount);
	m_pkNodes[i32Node].m_i32Next = m_i32FreeList;
	m_pkNodes[i32Node].m_i32Height = -1;
	m_i32FreeList = i32Node;
	--m_i32NodeCount;
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::InsertLeaf(VeInt32 i32Node)
{
	++m_i32InsertionCount;

	if(m_i32Root == NULL_NODE)
	{
		m_i32Root = i32Node;
		m_pkNodes[m_i32Root].m_i32Parent = NULL_NODE;
		return;
	}

	VeBoundingBox2D kBox = m_pkNodes[i32Node].m_kBox;
	VeInt32 i32Index = m_i32Root;
	while(m_pkNodes[i32Index].IsLeaf() == false)
	{
		VeInt32 i32Child0 = m_pkNodes[i32Index].m_i32Child0;
		VeInt32 i32Child1 = m_pkNodes[i32Index].m_i32Child1;

		VeFloat32 f32Area = m_pkNodes[i32Index].m_kBox.GetPerimeter();

		VeBoundingBox2D kCombinedBox;
		kCombinedBox.Combine(m_pkNodes[i32Index].m_kBox, kBox);
		VeFloat32 f32CombinedArea = kCombinedBox.GetPerimeter();

		VeFloat32 f32Cost = 2.0f * f32CombinedArea;

		VeFloat32 f32InheritanceCost = 2.0f * (f32CombinedArea - f32Area);

		VeFloat32 f32Cost1;
		if(m_pkNodes[i32Child0].IsLeaf())
		{
			VeBoundingBox2D kBox1;
			kBox1.Combine(kBox, m_pkNodes[i32Child0].m_kBox);
			f32Cost1 = kBox1.GetPerimeter() + f32InheritanceCost;
		}
		else
		{
			VeBoundingBox2D kBox1;
			kBox1.Combine(kBox, m_pkNodes[i32Child0].m_kBox);
			VeFloat32 f32OldArea = m_pkNodes[i32Child0].m_kBox.GetPerimeter();
			VeFloat32 f32NewArea = kBox1.GetPerimeter();
			f32Cost1 = (f32NewArea - f32OldArea) + f32InheritanceCost;
		}

		VeFloat32 f32Cost2;
		if(m_pkNodes[i32Child1].IsLeaf())
		{
			VeBoundingBox2D kBox1;
			kBox1.Combine(kBox, m_pkNodes[i32Child1].m_kBox);
			f32Cost2 = kBox1.GetPerimeter() + f32InheritanceCost;
		}
		else
		{
			VeBoundingBox2D kBox1;
			kBox1.Combine(kBox, m_pkNodes[i32Child1].m_kBox);
			VeFloat32 oldArea = m_pkNodes[i32Child1].m_kBox.GetPerimeter();
			VeFloat32 newArea = kBox1.GetPerimeter();
			f32Cost2 = newArea - oldArea + f32InheritanceCost;
		}

		if(f32Cost < f32Cost1 && f32Cost < f32Cost2)
		{
			break;
		}

		if(f32Cost1 < f32Cost2)
		{
			i32Index = i32Child0;
		}
		else
		{
			i32Index = i32Child1;
		}
	}

	VeInt32 i32Sibling = i32Index;

	VeInt32 i32OldParent = m_pkNodes[i32Sibling].m_i32Parent;
	VeInt32 i32NewParent = AllocateNode();
	m_pkNodes[i32NewParent].m_i32Parent = i32OldParent;
	m_pkNodes[i32NewParent].m_pvUserData = NULL;
	m_pkNodes[i32NewParent].m_kBox.Combine(kBox, m_pkNodes[i32Sibling].m_kBox);
	m_pkNodes[i32NewParent].m_i32Height = m_pkNodes[i32Sibling].m_i32Height + 1;

	if(i32OldParent != NULL_NODE)
	{
		if(m_pkNodes[i32OldParent].m_i32Child0 == i32Sibling)
		{
			m_pkNodes[i32OldParent].m_i32Child0 = i32NewParent;
		}
		else
		{
			m_pkNodes[i32OldParent].m_i32Child1 = i32NewParent;
		}
		m_pkNodes[i32NewParent].m_i32Child0 = i32Sibling;
		m_pkNodes[i32NewParent].m_i32Child1 = i32Node;
		m_pkNodes[i32Sibling].m_i32Parent = i32NewParent;
		m_pkNodes[i32Node].m_i32Parent = i32NewParent;
	}
	else
	{
		m_pkNodes[i32NewParent].m_i32Child0 = i32Sibling;
		m_pkNodes[i32NewParent].m_i32Child1 = i32Node;
		m_pkNodes[i32Sibling].m_i32Parent = i32NewParent;
		m_pkNodes[i32Node].m_i32Parent = i32NewParent;
		m_i32Root = i32NewParent;
	}

	i32Index = m_pkNodes[i32Node].m_i32Parent;
	while(i32Index != NULL_NODE)
	{
		i32Index = Balance(i32Index);

		VeInt32 i32Child0 = m_pkNodes[i32Index].m_i32Child0;
		VeInt32 i32Child1 = m_pkNodes[i32Index].m_i32Child1;

		VE_ASSERT(i32Child0 != NULL_NODE);
		VE_ASSERT(i32Child1 != NULL_NODE);

		m_pkNodes[i32Index].m_i32Height = 1 + VE_MAX(m_pkNodes[i32Child0].m_i32Height, m_pkNodes[i32Child1].m_i32Height);
		m_pkNodes[i32Index].m_kBox.Combine(m_pkNodes[i32Child0].m_kBox, m_pkNodes[i32Child1].m_kBox);

		i32Index = m_pkNodes[i32Index].m_i32Parent;
	}
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::RemoveLeaf(VeInt32 i32Node)
{
	if(i32Node == m_i32Root)
	{
		m_i32Root = NULL_NODE;
		return;
	}

	VeInt32 i32Parent = m_pkNodes[i32Node].m_i32Parent;
	VeInt32 i32GrandParent = m_pkNodes[i32Parent].m_i32Parent;
	VeInt32 i32Sibling;
	if(m_pkNodes[i32Parent].m_i32Child0 == i32Node)
	{
		i32Sibling = m_pkNodes[i32Parent].m_i32Child1;
	}
	else
	{
		i32Sibling = m_pkNodes[i32Parent].m_i32Child0;
	}

	if(i32GrandParent != NULL_NODE)
	{
		if(m_pkNodes[i32GrandParent].m_i32Child0 == i32Parent)
		{
			m_pkNodes[i32GrandParent].m_i32Child0 = i32Sibling;
		}
		else
		{
			m_pkNodes[i32GrandParent].m_i32Child1 = i32Sibling;
		}
		m_pkNodes[i32Sibling].m_i32Parent = i32GrandParent;
		FreeNode(i32Parent);

		VeInt32 i32Index = i32GrandParent;
		while(i32Index != NULL_NODE)
		{
			i32Index = Balance(i32Index);

			VeInt32 i32Child0 = m_pkNodes[i32Index].m_i32Child0;
			VeInt32 i32Child1 = m_pkNodes[i32Index].m_i32Child1;

			m_pkNodes[i32Index].m_kBox.Combine(m_pkNodes[i32Child0].m_kBox, m_pkNodes[i32Child1].m_kBox);
			m_pkNodes[i32Index].m_i32Height = 1 + VE_MAX(m_pkNodes[i32Child0].m_i32Height, m_pkNodes[i32Child1].m_i32Height);

			i32Index = m_pkNodes[i32Index].m_i32Parent;
		}
	}
	else
	{
		m_i32Root = i32Sibling;
		m_pkNodes[i32Sibling].m_i32Parent = NULL_NODE;
		FreeNode(i32Parent);
	}
}
//--------------------------------------------------------------------------
VeInt32 VeBoundingTree2D::Balance(VeInt32 iA)
{
	VE_ASSERT(iA != NULL_NODE);

	Node* A = m_pkNodes + iA;
	if (A->IsLeaf() || A->m_i32Height < 2)
	{
		return iA;
	}

	VeInt32 iB = A->m_i32Child0;
	VeInt32 iC = A->m_i32Child1;
	VE_ASSERT(0 <= iB && iB < m_i32NodeCapacity);
	VE_ASSERT(0 <= iC && iC < m_i32NodeCapacity);

	Node* B = m_pkNodes + iB;
	Node* C = m_pkNodes + iC;

	VeInt32 i32Balance = C->m_i32Height - B->m_i32Height;

	if(i32Balance > 1)
	{
		VeInt32 iF = C->m_i32Child0;
		VeInt32 iG = C->m_i32Child1;
		Node* F = m_pkNodes + iF;
		Node* G = m_pkNodes + iG;
		VE_ASSERT(0 <= iF && iF < m_i32NodeCapacity);
		VE_ASSERT(0 <= iG && iG < m_i32NodeCapacity);

		C->m_i32Child0 = iA;
		C->m_i32Parent = A->m_i32Parent;
		A->m_i32Parent = iC;

		if(C->m_i32Parent != NULL_NODE)
		{
			if(m_pkNodes[C->m_i32Parent].m_i32Child0 == iA)
			{
				m_pkNodes[C->m_i32Parent].m_i32Child0 = iC;
			}
			else
			{
				VE_ASSERT(m_pkNodes[C->m_i32Parent].m_i32Child1 == iA);
				m_pkNodes[C->m_i32Parent].m_i32Child1 = iC;
			}
		}
		else
		{
			m_i32Root = iC;
		}

		if(F->m_i32Height > G->m_i32Height)
		{
			C->m_i32Child1 = iF;
			A->m_i32Child1 = iG;
			G->m_i32Parent = iA;
			A->m_kBox.Combine(B->m_kBox, G->m_kBox);
			C->m_kBox.Combine(A->m_kBox, F->m_kBox);

			A->m_i32Height = 1 + VE_MAX(B->m_i32Height, G->m_i32Height);
			C->m_i32Height = 1 + VE_MAX(A->m_i32Height, F->m_i32Height);
		}
		else
		{
			C->m_i32Child1 = iG;
			A->m_i32Child1 = iF;
			F->m_i32Parent = iA;
			A->m_kBox.Combine(B->m_kBox, F->m_kBox);
			C->m_kBox.Combine(A->m_kBox, G->m_kBox);

			A->m_i32Height = 1 + VE_MAX(B->m_i32Height, F->m_i32Height);
			C->m_i32Height = 1 + VE_MAX(A->m_i32Height, G->m_i32Height);
		}

		return iC;
	}

	if(i32Balance < -1)
	{
		VeInt32 iD = B->m_i32Child0;
		VeInt32 iE = B->m_i32Child1;
		Node* D = m_pkNodes + iD;
		Node* E = m_pkNodes + iE;
		VE_ASSERT(0 <= iD && iD < m_i32NodeCapacity);
		VE_ASSERT(0 <= iE && iE < m_i32NodeCapacity);

		B->m_i32Child0 = iA;
		B->m_i32Parent = A->m_i32Parent;
		A->m_i32Parent = iB;

		if(B->m_i32Parent != NULL_NODE)
		{
			if(m_pkNodes[B->m_i32Parent].m_i32Child0 == iA)
			{
				m_pkNodes[B->m_i32Parent].m_i32Child0 = iB;
			}
			else
			{
				VE_ASSERT(m_pkNodes[B->m_i32Parent].m_i32Child1 == iA);
				m_pkNodes[B->m_i32Parent].m_i32Child1 = iB;
			}
		}
		else
		{
			m_i32Root = iB;
		}

		if(D->m_i32Height > E->m_i32Height)
		{
			B->m_i32Child1 = iD;
			A->m_i32Child0 = iE;
			E->m_i32Parent = iA;
			A->m_kBox.Combine(C->m_kBox, E->m_kBox);
			B->m_kBox.Combine(A->m_kBox, D->m_kBox);

			A->m_i32Height = 1 + VE_MAX(C->m_i32Height, E->m_i32Height);
			B->m_i32Height = 1 + VE_MAX(A->m_i32Height, D->m_i32Height);
		}
		else
		{
			B->m_i32Child1 = iE;
			A->m_i32Child0 = iD;
			D->m_i32Parent = iA;
			A->m_kBox.Combine(C->m_kBox, D->m_kBox);
			B->m_kBox.Combine(A->m_kBox, E->m_kBox);

			A->m_i32Height = 1 + VE_MAX(C->m_i32Height, D->m_i32Height);
			B->m_i32Height = 1 + VE_MAX(A->m_i32Height, E->m_i32Height);
		}

		return iB;
	}

	return iA;
}
//--------------------------------------------------------------------------
VeInt32 VeBoundingTree2D::ComputeHeight() const
{
	return ComputeHeight(m_i32Root);
}
//--------------------------------------------------------------------------
VeInt32 VeBoundingTree2D::ComputeHeight(VeInt32 i32Node) const
{
	VE_ASSERT(0 <= i32Node && i32Node < m_i32NodeCapacity);
	Node* pkNode = m_pkNodes + i32Node;

	if(pkNode->IsLeaf())
	{
		return 0;
	}

	VeInt32 i32Height0 = ComputeHeight(pkNode->m_i32Child0);
	VeInt32 i32Height1 = ComputeHeight(pkNode->m_i32Child1);
	return 1 + VE_MAX(i32Height0, i32Height1);
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::ValidateStructure(VeInt32 i32Index) const
{
	if(i32Index == NULL_NODE)
	{
		return;
	}

	if(i32Index == m_i32Root)
	{
		VE_ASSERT(m_pkNodes[i32Index].m_i32Parent == NULL_NODE);
	}

	const Node* pkNode = m_pkNodes + i32Index;

	VeInt32 i32Child0 = pkNode->m_i32Child0;
	VeInt32 i32Child1 = pkNode->m_i32Child1;

	if(pkNode->IsLeaf())
	{
		VE_ASSERT(i32Child0 == NULL_NODE);
		VE_ASSERT(i32Child1 == NULL_NODE);
		VE_ASSERT(pkNode->m_i32Height == 0);
		return;
	}

	VE_ASSERT(0 <= i32Child0 && i32Child0 < m_i32NodeCapacity);
	VE_ASSERT(0 <= i32Child1 && i32Child1 < m_i32NodeCapacity);

	VE_ASSERT(m_pkNodes[i32Child0].m_i32Parent == i32Index);
	VE_ASSERT(m_pkNodes[i32Child1].m_i32Parent == i32Index);

	ValidateStructure(i32Child0);
	ValidateStructure(i32Child1);
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::ValidateMetrics(VeInt32 i32Index) const
{
	if (i32Index == NULL_NODE)
	{
		return;
	}

	const Node* pkNode = m_pkNodes + i32Index;

	VeInt32 i32Child0 = pkNode->m_i32Child0;
	VeInt32 i32Child1 = pkNode->m_i32Child1;

	if(pkNode->IsLeaf())
	{
		VE_ASSERT(i32Child0 == NULL_NODE);
		VE_ASSERT(i32Child1 == NULL_NODE);
		VE_ASSERT(pkNode->m_i32Height == 0);
		return;
	}

	VE_ASSERT(0 <= i32Child0 && i32Child0 < m_i32NodeCapacity);
	VE_ASSERT(0 <= i32Child1 && i32Child1 < m_i32NodeCapacity);

	VeInt32 i32Height0 = m_pkNodes[i32Child0].m_i32Height;
	VeInt32 i32Height1 = m_pkNodes[i32Child1].m_i32Height;
	VeInt32 i32Height;
	i32Height = 1 + VE_MAX(i32Height0, i32Height1);
	VE_ASSERT(pkNode->m_i32Height == i32Height);

	VeBoundingBox2D kBox;
	kBox.Combine(m_pkNodes[i32Child0].m_kBox, m_pkNodes[i32Child1].m_kBox);

	VE_ASSERT(kBox.m_kMin == pkNode->m_kBox.m_kMin);
	VE_ASSERT(kBox.m_kMax == pkNode->m_kBox.m_kMax);

	ValidateMetrics(i32Child0);
	ValidateMetrics(i32Child1);
}
//--------------------------------------------------------------------------
VeInt32 VeBoundingTree2D::CreateProxy(const VeBoundingBox2D& kBox,
	void* pvUserData)
{
	VeInt32 i32Proxy = AllocateNode();

	VeVector2D kVec(BOX_EXT, BOX_EXT);
	m_pkNodes[i32Proxy].m_kBox.m_kMin = kBox.m_kMin - kVec;
	m_pkNodes[i32Proxy].m_kBox.m_kMax = kBox.m_kMax + kVec;
	m_pkNodes[i32Proxy].m_pvUserData = pvUserData;
	m_pkNodes[i32Proxy].m_i32Height = 0;

	InsertLeaf(i32Proxy);

	return i32Proxy;
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::DestroyProxy(VeInt32 i32Proxy)
{
	VE_ASSERT(0 <= i32Proxy && i32Proxy < m_i32NodeCapacity);
	VE_ASSERT(m_pkNodes[i32Proxy].IsLeaf());
	RemoveLeaf(i32Proxy);
	FreeNode(i32Proxy);
}
//--------------------------------------------------------------------------
bool VeBoundingTree2D::MoveProxy(VeInt32 i32Proxy,
	const VeBoundingBox2D& kBox, const VeVector2D& kDisplacement)
{
	VE_ASSERT(0 <= i32Proxy && i32Proxy < m_i32NodeCapacity);

	VE_ASSERT(m_pkNodes[i32Proxy].IsLeaf());

	if (m_pkNodes[i32Proxy].m_kBox.Contains(kBox))
	{
		return false;
	}

	RemoveLeaf(i32Proxy);

	VeBoundingBox2D kCopy = kBox;
	VeVector2D r(BOX_EXT, BOX_EXT);
	kCopy.m_kMin = kCopy.m_kMin - r;
	kCopy.m_kMax = kCopy.m_kMax + r;

	VeVector2D kDisp = BOX_MUL * kDisplacement;

	if(kDisp.x < 0.0f)
	{
		kCopy.m_kMin.x += kDisp.x;
	}
	else
	{
		kCopy.m_kMax.x += kDisp.x;
	}

	if (kDisp.y < 0.0f)
	{
		kCopy.m_kMin.y += kDisp.y;
	}
	else
	{
		kCopy.m_kMax.y += kDisp.y;
	}

	m_pkNodes[i32Proxy].m_kBox = kCopy;

	InsertLeaf(i32Proxy);
	return true;
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::Validate() const
{
	ValidateStructure(m_i32Root);
	ValidateMetrics(m_i32Root);

	VeInt32 i32FreeCount = 0;
	VeInt32 i32FreeIndex = m_i32FreeList;
	while(i32FreeIndex != NULL_NODE)
	{
		VE_ASSERT(0 <= i32FreeIndex && i32FreeIndex < m_i32NodeCapacity);
		i32FreeIndex = m_pkNodes[i32FreeIndex].m_i32Next;
		++i32FreeCount;
	}

	VE_ASSERT(GetHeight() == ComputeHeight());
	VE_ASSERT(m_i32NodeCount + i32FreeCount == m_i32NodeCapacity);
}
//--------------------------------------------------------------------------
VeInt32 VeBoundingTree2D::GetHeight() const
{
	if (m_i32Root == NULL_NODE)
	{
		return 0;
	}

	return m_pkNodes[m_i32Root].m_i32Height;
}
//--------------------------------------------------------------------------
VeInt32 VeBoundingTree2D::GetMaxBalance() const
{
	VeInt32 i32MaxBalance = 0;
	for(VeInt32 i(0); i < m_i32NodeCapacity; ++i)
	{
		const Node* pkNode = m_pkNodes + i;
		if (pkNode->m_i32Height <= 1)
		{
			continue;
		}

		VE_ASSERT(pkNode->IsLeaf() == false);

		VeInt32 i32Child0 = pkNode->m_i32Child0;
		VeInt32 i32Child1 = pkNode->m_i32Child1;
		VeInt32 i32Balance = VeTAbs(m_pkNodes[i32Child1].m_i32Height - m_pkNodes[i32Child0].m_i32Height);
		i32MaxBalance = VE_MAX(i32MaxBalance, i32Balance);
	}

	return i32MaxBalance;
}
//--------------------------------------------------------------------------
VeFloat32 VeBoundingTree2D::GetAreaRatio() const
{
	if(m_i32Root == NULL_NODE)
	{
		return 0.0f;
	}

	const Node* pkRoot = m_pkNodes + m_i32Root;
	VeFloat32 rootArea = pkRoot->m_kBox.GetPerimeter();

	VeFloat32 totalArea = 0.0f;
	for(VeInt32 i = 0; i < m_i32NodeCapacity; ++i)
	{
		const Node* pkNode = m_pkNodes + i;
		if(pkNode->m_i32Height < 0)
		{
			continue;
		}

		totalArea += pkNode->m_kBox.GetPerimeter();
	}

	return totalArea / rootArea;
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::RebuildBottomUp()
{
	VeInt32* pkNodes = (VeInt32*)VeMalloc(m_i32NodeCount * sizeof(VeInt32));
	VeInt32 i32Count = 0;

	for(VeInt32 i = 0; i < m_i32NodeCapacity; ++i)
	{
		if(m_pkNodes[i].m_i32Height < 0)
		{
			continue;
		}

		if (m_pkNodes[i].IsLeaf())
		{
			m_pkNodes[i].m_i32Parent = NULL_NODE;
			pkNodes[i32Count] = i;
			++i32Count;
		}
		else
		{
			FreeNode(i);
		}
	}

	while(i32Count > 1)
	{
		VeFloat32 f32MinCost = VE_MAXFLOAT_F;
		VeInt32 i32Min0 = -1, i32Min1 = -1;
		for(VeInt32 i = 0; i < i32Count; ++i)
		{
			VeBoundingBox2D kBox0 = m_pkNodes[pkNodes[i]].m_kBox;

			for(VeInt32 j = i + 1; j < i32Count; ++j)
			{
				VeBoundingBox2D kBox1 = m_pkNodes[pkNodes[j]].m_kBox;
				VeBoundingBox2D kComb;
				kComb.Combine(kBox0, kBox1);
				VeFloat32 f32Cost = kComb.GetPerimeter();
				if (f32Cost < f32MinCost)
				{
					i32Min0 = i;
					i32Min1 = j;
					f32MinCost = f32Cost;
				}
			}
		}

		VeInt32 i32Index0 = pkNodes[i32Min0];
		VeInt32 i32Index1 = pkNodes[i32Min1];
		Node* pkChild0 = m_pkNodes + i32Index0;
		Node* pkChild1 = m_pkNodes + i32Index1;

		VeInt32 i32ParentIndex = AllocateNode();
		Node* pkParent = m_pkNodes + i32ParentIndex;
		pkParent->m_i32Child0 = i32Index0;
		pkParent->m_i32Child1 = i32Index1;
		pkParent->m_i32Height = 1 + VE_MAX(pkChild0->m_i32Height, pkChild1->m_i32Height);
		pkParent->m_kBox.Combine(pkChild0->m_kBox, pkChild1->m_kBox);
		pkParent->m_i32Parent = NULL_NODE;

		pkChild0->m_i32Parent = i32ParentIndex;
		pkChild1->m_i32Parent = i32ParentIndex;

		pkNodes[i32Min1] = pkNodes[i32Count-1];
		pkNodes[i32Min0] = i32ParentIndex;
		--i32Count;
	}

	m_i32Root = pkNodes[0];
	VeFree(pkNodes);

	Validate();
}
//--------------------------------------------------------------------------
void VeBoundingTree2D::ShiftOrigin(const VeVector2D& kNewOrigin)
{
	for(VeInt32 i = 0; i < m_i32NodeCapacity; ++i)
	{
		m_pkNodes[i].m_kBox.m_kMin -= kNewOrigin;
		m_pkNodes[i].m_kBox.m_kMax -= kNewOrigin;
	}
}
//--------------------------------------------------------------------------
