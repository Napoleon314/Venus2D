////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBoundingTree.h
//  Version:     v1.00
//  Created:     29/1/2015 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeBoundingTree2D : public VeMemObject
{
public:
	struct Node
	{
		bool IsLeaf() const
		{
			return m_i32Child0 == -1;
		}

		VeBoundingBox2D m_kBox;
		void* m_pvUserData;

		union
		{
			VeInt32 m_i32Parent;
			VeInt32 m_i32Next;
		};

		VeInt32 m_i32Child0;
		VeInt32 m_i32Child1;
		VeInt32 m_i32Height;
	};

	VeBoundingTree2D();

	~VeBoundingTree2D();

	VE_INLINE void* GetUserData(VeInt32 proxyId) const;

	VE_INLINE const VeBoundingBox2D& GetFatAABB(VeInt32 proxyId) const;

	VeInt32 CreateProxy(const VeBoundingBox2D& kBox, void* pvUserData);

	void DestroyProxy(VeInt32 i32Poxy);

	bool MoveProxy(VeInt32 i32Proxy, const VeBoundingBox2D& kBox, const VeVector2D& kDisplacement);

	void Validate() const;

	VeInt32 GetHeight() const;

	VeInt32 GetMaxBalance() const;

	VeFloat32 GetAreaRatio() const;

	void RebuildBottomUp();

	void ShiftOrigin(const VeVector2D& kNewOrigin);

	template <typename T>
	void Query(T* pkCallback, bool (T::*pfuncCall)(void*), const VeBoundingBox2D& kBox) const
	{
		VeVector<VeInt32> kStack;
		kStack.Reserve(256);
		kStack.PushBack(m_i32Root);

		while(kStack.Size())
		{
			VeInt32 i32Node = kStack.Back();
			kStack.PopBack();
			if (i32Node == -1)
			{
				continue;
			}

			const Node* pkNode = m_pkNodes + i32Node;

			if(VeBoundingBox2D::TestOverlap(pkNode->m_kBox, kBox))
			{
				if(pkNode->IsLeaf())
				{
					bool bProceed = (pkCallback->*pfuncCall)(GetUserData(i32Node));
					if (bProceed == false)
					{
						return;
					}
				}
				else
				{
					kStack.PushBack(pkNode->m_i32Child0);
					kStack.PushBack(pkNode->m_i32Child1);
				}
			}
		}
	}

private:
	VeInt32 AllocateNode();

	void FreeNode(VeInt32 i32Node);

	void InsertLeaf(VeInt32 i32Node);

	void RemoveLeaf(VeInt32 i32Node);

	VeInt32 Balance(VeInt32 i32Node);

	VeInt32 ComputeHeight() const;

	VeInt32 ComputeHeight(VeInt32 nodeId) const;

	void ValidateStructure(VeInt32 i32Index) const;

	void ValidateMetrics(VeInt32 i32Index) const;

	VeInt32 m_i32Root;
	Node* m_pkNodes;
	VeInt32 m_i32NodeCount;
	VeInt32 m_i32NodeCapacity;
	VeInt32 m_i32FreeList;
	VeUInt32 m_u32Path;
	VeInt32 m_i32InsertionCount;

};

#ifndef VE_NO_INLINE
#	include "VeBoundingTree.inl"
#endif
