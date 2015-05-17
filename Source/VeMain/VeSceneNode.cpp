////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneNode.cpp
//  Version:     v1.00
//  Created:     11/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeSceneNode.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeSceneNode, VeObject);
//--------------------------------------------------------------------------
VeSceneNode::VeSceneNode()
	: m_u32VisibleMask(VE_INFINITE), m_pkParent(NULL)
	, m_u32ActionUpdateFrame(0)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeSceneNode::~VeSceneNode()
{
	StopAllActions();
	DetachFromParent();
	DetachAllChildren();
	DetachAllRenderables();
}
//--------------------------------------------------------------------------
void VeSceneNode::AttachChild(VeSceneNode* pkChild)
{
	VE_ASSERT(pkChild && pkChild != this);
	if(pkChild->m_pkParent != this)
	{
		if(!(pkChild->m_kNode.IsAttach()))
		{
			pkChild->IncRefCount();
		}
		m_kChildren.AttachBack(pkChild->m_kNode);
		pkChild->m_pkParent = this;
	}
}
//--------------------------------------------------------------------------
void VeSceneNode::DetachFromParent()
{
	if(m_pkParent)
	{
		VE_ASSERT(m_kNode.IsAttach(m_pkParent->m_kChildren));
		m_pkParent = NULL;
		m_kNode.Detach();
		DecRefCount();
	}
}
//--------------------------------------------------------------------------
void VeSceneNode::DetachAllChildren()
{
	m_kChildren.BeginIterator();
	while(!m_kChildren.IsEnd())
	{
		VeSceneNode* pkChild = m_kChildren.GetIterNode()->m_tContent;
		m_kChildren.Next();
		pkChild->DetachFromParent();
	}
	VE_ASSERT(m_kChildren.Empty());
}
//--------------------------------------------------------------------------
void VeSceneNode::AttachRenderable(VeSceneRenderable* pkRenderable)
{
	VE_ASSERT(pkRenderable);
	if(!pkRenderable->m_kNode.IsAttach())
	{
		pkRenderable->IncRefCount();
	}
	m_kRenderableList.AttachBack(pkRenderable->m_kNode);
}
//--------------------------------------------------------------------------
void VeSceneNode::DetachRenderable(VeSceneRenderable* pkRenderable)
{
	if(pkRenderable && pkRenderable->m_kNode.IsAttach(m_kRenderableList))
	{
		pkRenderable->Detach();
	}
}
//--------------------------------------------------------------------------
void VeSceneNode::DetachAllRenderables()
{
	m_kRenderableList.BeginIterator();
	while(!m_kRenderableList.IsEnd())
	{
		VeSceneRenderable* pkRenderable = m_kRenderableList.GetIterNode()->m_tContent;
		m_kRenderableList.Next();
		DetachRenderable(pkRenderable);
	}
	VE_ASSERT(m_kRenderableList.Empty());
}
//--------------------------------------------------------------------------
void VeSceneNode::Visit(VeRenderQueue& kQueue)
{
	UpdateActions();
	m_kRenderableList.BeginIterator();
	while(!m_kRenderableList.IsEnd())
	{
		VeSceneRenderable* pkIter = m_kRenderableList.GetIterNode()->m_tContent;
		m_kRenderableList.Next();
		pkIter->Visit(kQueue, m_u32VisibleMask);
	}
	BeginChild();
	VeSceneNode* pkIter = NextChild();
	while(pkIter)
	{
		if(pkIter->GetVisibleMask())
		{
			pkIter->Visit(kQueue);
		}
		pkIter = NextChild();
	}
	EndChild();
}
//--------------------------------------------------------------------------
void VeSceneNode::BeginChild()
{
	m_kChildren.BeginIterator();
}
//--------------------------------------------------------------------------
VeSceneNode* VeSceneNode::NextChild()
{
	VeSceneNode* pkRes(NULL);
	if(!m_kChildren.IsEnd())
	{
		pkRes = m_kChildren.GetIterNode()->m_tContent;
		m_kChildren.Next();
	}
	return pkRes;
}
//--------------------------------------------------------------------------
void VeSceneNode::BeginChildR()
{
	m_kChildren.BeginIteratorFromLast();
}
//--------------------------------------------------------------------------
VeSceneNode* VeSceneNode::NextChildR()
{
	VeSceneNode* pkRes(NULL);
	if(!m_kChildren.IsEnd())
	{
		pkRes = m_kChildren.GetIterNode()->m_tContent;
		m_kChildren.Pre();
	}
	return pkRes;
}
//--------------------------------------------------------------------------
void VeSceneNode::EndChild()
{
	m_kChildren.EndIterator();
}
//--------------------------------------------------------------------------
void VeSceneNode::BeginRenderable()
{
	m_kRenderableList.BeginIterator();
}
//--------------------------------------------------------------------------
VeSceneRenderable* VeSceneNode::NextRenderable()
{
	VeSceneRenderable* pkRes(NULL);
	if(!m_kRenderableList.IsEnd())
	{
		pkRes = m_kRenderableList.GetIterNode()->m_tContent;
		m_kRenderableList.Next();
	}
	return pkRes;
}
//--------------------------------------------------------------------------
void VeSceneNode::BeginRenderableR()
{
	m_kRenderableList.BeginIteratorFromLast();
}
//--------------------------------------------------------------------------
VeSceneRenderable* VeSceneNode::NextRenderableR()
{
	VeSceneRenderable* pkRes(NULL);
	if(!m_kRenderableList.IsEnd())
	{
		pkRes = m_kRenderableList.GetIterNode()->m_tContent;
		m_kRenderableList.Pre();
	}
	return pkRes;
}
//--------------------------------------------------------------------------
void VeSceneNode::EndRenderable()
{
	m_kRenderableList.EndIterator();
}
//--------------------------------------------------------------------------
void VeSceneNode::RunAction(VeAction* pkAction)
{
	VE_ASSERT(pkAction);
	if(!pkAction->m_kNode.IsAttach())
	{
		pkAction->IncRefCount();
	}
	m_kActionList.AttachBack(pkAction->m_kNode);
}
//--------------------------------------------------------------------------
class RunActionCall_S : public VeRefObject
{
public:
	RunActionCall_S(lua_State* pkThread, VeInt32 i32Ref);

	VeDeclActDelegate(RunActionCall_S, OnEvent);
	lua_State* m_pkThread;
	VeInt32 m_i32Ref;
	VeRefNode<VeRefObject*> m_kNode;

};
//--------------------------------------------------------------------------
RunActionCall_S::RunActionCall_S(lua_State* pkThread, VeInt32 i32Ref)
	: m_pkThread(pkThread), m_i32Ref(i32Ref)
{
	m_kNode.m_tContent = this;
	VeInitDelegate(RunActionCall_S, OnEvent);
	g_pLua->AddCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
VeImplActDelegate(RunActionCall_S, OnEvent, spAction)
{
	VeLuaBind::Resume(m_pkThread, m_i32Ref, g_pLua->GetLua(), 0);
	g_pLua->DelCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
void VeSceneNode::RunAction_S(lua_State* pkState,
	VeFiniteTimeAction* pkAction)
{
	VeInt32 i32Ref = VeLuaBind::Pause(pkState);
	RunActionCall_S* pkCall = VE_NEW RunActionCall_S(pkState, i32Ref);
	RunAction(VeSequence::CreateWithTwoActions(pkAction, VeActionCall::Create(pkCall->m_kOnEvent)));
}
//--------------------------------------------------------------------------
class RunActionCall_A : public VeRefObject
{
public:
	RunActionCall_A(const VeLuaSyncHolderPtr& spHolder);

	VeDeclActDelegate(RunActionCall_A, OnEvent);
	VeLuaSyncHolderPtr m_spHolder;
	VeRefNode<VeRefObject*> m_kNode;

};
//--------------------------------------------------------------------------
RunActionCall_A::RunActionCall_A(const VeLuaSyncHolderPtr& spHolder)
	: m_spHolder(spHolder)
{
	m_kNode.m_tContent = this;
	VeInitDelegate(RunActionCall_A, OnEvent);
	g_pLua->AddCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
VeImplActDelegate(RunActionCall_A, OnEvent, spAction)
{
	m_spHolder->DecRef();
	m_spHolder = NULL;
	g_pLua->DelCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
VeLuaSyncHolder* VeSceneNode::RunAction_A(lua_State* pkState,
	VeFiniteTimeAction* pkAction)
{
	VeLuaSyncHolderPtr spHolder = VE_NEW VeLuaSyncHolder();
	spHolder->IncRef();
	RunActionCall_A* pkCall = VE_NEW RunActionCall_A(spHolder);
	RunAction(VeSequence::CreateWithTwoActions(pkAction, VeActionCall::Create(pkCall->m_kOnEvent)));
	return spHolder;
}
//--------------------------------------------------------------------------
void VeSceneNode::StopAllActions()
{
	m_kActionList.BeginIterator();
	while(!m_kActionList.IsEnd())
	{
		VeAction* pkAction = m_kActionList.GetIterNode()->m_tContent;
		m_kActionList.Next();
		pkAction->m_kNode.Detach();
		pkAction->Stop();
		pkAction->DecRefCount();
	}
	VE_ASSERT(m_kActionList.Empty());
}
//--------------------------------------------------------------------------
void VeSceneNode::StopAction(VeAction* pkAction)
{
	VE_ASSERT(pkAction);
	if(pkAction->m_kNode.IsAttach(m_kActionList))
	{
		pkAction->m_kNode.Detach();
		pkAction->Stop();
		pkAction->DecRefCount();
	}
}
//--------------------------------------------------------------------------
bool VeSceneNode::HasRunningAction()
{
	return m_kActionList.Size() ? true : false;
}
//--------------------------------------------------------------------------
void VeSceneNode::UpdateActions()
{
	VeUInt32 u32CurFrame = g_pRenderFrameManager->GetFrameCount();
	if(u32CurFrame > m_u32ActionUpdateFrame)
	{
		m_u32ActionUpdateFrame = u32CurFrame;
		m_kActionList.BeginIterator();
		while(!m_kActionList.IsEnd())
		{
			VeAction* pkAction = m_kActionList.GetIterNode()->m_tContent;
			m_kActionList.Next();
			if(pkAction->m_pkTarget)
			{
				pkAction->Update(g_pTime->GetTime());
				if(pkAction->IsDone())
				{
					StopAction(pkAction);
				}
			}
			else
			{
				pkAction->Start(this, g_pTime->GetTime());
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeSceneNode::From(VeBinaryIStream& kIn)
{
	kIn >> m_u32VisibleMask;
}
//--------------------------------------------------------------------------
void VeSceneNode::To(VeBinaryOStream& kOut) const
{
	kOut << m_u32VisibleMask;
}
//--------------------------------------------------------------------------
void VeSceneNode::From(VeXMLElement* pkElement)
{
	m_u32VisibleMask = pkElement->Attribute("mask", 0xffffffffu);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSceneNode)
{
	Module() [
		Class<VeSceneNode>().
			Def("SetVisibleMask", &VeSceneNode::SetVisibleMask).
			Def("GetVisibleMask", &VeSceneNode::GetVisibleMask).
			Def("AttachChild", &VeSceneNode::AttachChild).
			Def("DetachFromParent", &VeSceneNode::DetachFromParent).
			Def("DetachAllChildren", &VeSceneNode::DetachAllChildren).
			Def("AttachRenderable", &VeSceneNode::AttachRenderable).
			Def("DetachRenderable", &VeSceneNode::DetachRenderable).
			Def("DetachAllRenderables", &VeSceneNode::DetachAllRenderables).
			Def("RunAction", &VeSceneNode::RunAction).
			Def("RunAction_S", &VeSceneNode::RunAction_S).
			Def("RunAction_A", &VeSceneNode::RunAction_A).
			Def("StopAllActions", &VeSceneNode::StopAllActions).
			Def("StopAction", &VeSceneNode::StopAction)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSceneNode2D, VeSceneNode);
//--------------------------------------------------------------------------
VeSceneNode2D::VeSceneNode2D() : m_f32ZOrder(0), m_pkRenderNode(NULL)
	, m_pkContext(NULL), m_u32UpdateFrame(0)
{
	m_kZOrderMap[0] = VE_INFINITE;
	m_kScale = VeVector2D(1.0f, 1.0f);
	m_kMulColor = VeColor::WHITE;
	m_kAddColor = VeColor::ZERO;
	m_bDirty = true;
}
//--------------------------------------------------------------------------
VeSceneNode2D::~VeSceneNode2D()
{
	DetachFromParent();
	DetachAllChildren();
	DetachAllRenderables();
	VE_SAFE_DELETE(m_pkRenderNode);
	VE_ASSERT(m_kZOrderMap.Size() == 1 && m_kZOrderChildren.Empty());
}
//--------------------------------------------------------------------------
void VeSceneNode2D::AttachChild(VeSceneNode* pkChild)
{
	VE_ASSERT(pkChild && pkChild != this);
	VeSceneNode2D* pkNode2D = VeDynamicCast(VeSceneNode2D, pkChild);
	if(pkNode2D)
	{
		if(pkNode2D->m_pkParent != this)
		{
			if(!(pkNode2D->m_kNode.IsAttach()))
			{
				pkNode2D->IncRefCount();
			}
			if(pkNode2D->m_f32ZOrder)
			{
				VeMap<VeFloat32, VeUInt32>::iterator itFind = m_kZOrderMap.Find(pkNode2D->m_f32ZOrder);
				if(itFind != m_kZOrderMap.End())
				{
					VE_ASSERT(itFind->m_tSecond < m_kZOrderChildren.Size());
					m_kZOrderChildren[itFind->m_tSecond]->AttachBack(pkNode2D->m_kNode);
				}
				else
				{
					m_kZOrderMap[pkNode2D->m_f32ZOrder] = m_kZOrderChildren.Size();
					m_kZOrderChildren.Increase();
					m_kZOrderChildren.Back() = CreateNodeList();
					m_kZOrderChildren.Back()->AttachBack(pkNode2D->m_kNode);
				}
			}
			else
			{
				m_kChildren.AttachBack(pkNode2D->m_kNode);
			}
			pkNode2D->m_pkParent = this;
			pkNode2D->UpdateContext(m_pkContext);
			m_bDirty = true;
		}
	}
	else
	{
		VeSceneNode::AttachChild(pkChild);
	}
}
//--------------------------------------------------------------------------
void VeSceneNode2D::DetachFromParent()
{
	m_bDirty = true;
	UpdateContext(NULL);
	VeSceneNode2D* pkParent = VeDynamicCast(VeSceneNode2D, m_pkParent);
	if(m_f32ZOrder && pkParent)
	{
		VeRefList<VeSceneNode*>* pkNodeList = m_kNode.GetRefList();
		VE_ASSERT(pkNodeList);
		m_pkParent = NULL;
		m_kNode.Detach();
		if(pkNodeList->Empty())
		{
			VeMap<VeFloat32, VeUInt32>::iterator itFind = pkParent->m_kZOrderMap.Find(m_f32ZOrder);
			VE_ASSERT(itFind != pkParent->m_kZOrderMap.End() && itFind->m_tSecond < pkParent->m_kZOrderChildren.Size());
			VeUInt32 u32Index(itFind->m_tSecond);
			VeRefList<VeSceneNode*>* pkList = pkParent->m_kZOrderChildren[u32Index];
			VE_ASSERT(pkNodeList == pkList);
			pkParent->m_kZOrderMap.Erase(itFind);
			DestoryNodeList(pkList);
			if(u32Index < (pkParent->m_kZOrderChildren.Size() - 1))
			{
				pkParent->m_kZOrderChildren[u32Index] = pkParent->m_kZOrderChildren.Back();
				VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, pkParent->m_kZOrderChildren.Back()->GetHeadNode()->m_tContent);
				VE_ASSERT(pkNode);
				pkParent->m_kZOrderMap[pkNode->m_f32ZOrder] = u32Index;
			}
			pkParent->m_kZOrderChildren.PopBack();
			VE_ASSERT(pkParent->m_kZOrderMap.Size() == (pkParent->m_kZOrderChildren.Size() + 1));
		}
		DecRefCount();
	}
	else
	{
		VeSceneNode::DetachFromParent();
	}
}
//--------------------------------------------------------------------------
void VeSceneNode2D::DetachAllChildren()
{
	for(VeUInt32 i(0); i < m_kZOrderChildren.Size(); ++i)
	{
		VeRefList<VeSceneNode*>* it = m_kZOrderChildren[i];
		it->BeginIterator();
		while(!it->IsEnd())
		{
			VeSceneNode2D* pkChild = VeDynamicCast(VeSceneNode2D, it->GetIterNode()->m_tContent);
			VE_ASSERT(pkChild);
			it->Next();
			pkChild->m_pkParent = NULL;
			pkChild->m_kNode.Detach();
			pkChild->DecRefCount();
		}
		DestoryNodeList(it);
	}
	m_kZOrderChildren.Clear();
	m_kZOrderMap.Clear();
	m_kZOrderMap[0] = VE_INFINITE;
	VeSceneNode::DetachAllChildren();
}
//--------------------------------------------------------------------------
void VeSceneNode2D::AttachRenderable(VeSceneRenderable* pkRenderable)
{
	VE_ASSERT(pkRenderable);
	VeSceneNode::AttachRenderable(pkRenderable);
	VeSceneRenderable2D* pkRenderable2D = VeDynamicCast(VeSceneRenderable2D, pkRenderable);
	if(pkRenderable2D)
	{
		pkRenderable2D->m_pkRenderNode->SetParent(m_pkContext);
	}
}
//--------------------------------------------------------------------------
void VeSceneNode2D::DetachRenderable(VeSceneRenderable* pkRenderable)
{
	VE_ASSERT(pkRenderable);
	VeSceneRenderable2D* pkRenderable2D = VeDynamicCast(VeSceneRenderable2D, pkRenderable);
	if(pkRenderable2D)
	{
		pkRenderable2D->m_pkRenderNode->SetParent(NULL);
	}
	VeSceneNode::DetachRenderable(pkRenderable);
}
//--------------------------------------------------------------------------
void VeSceneNode2D::Visit(VeRenderQueue& kQueue)
{
	UpdateActions();
	UpdateFromParent();
	m_kRenderableList.BeginIterator();
	while(!m_kRenderableList.IsEnd())
	{
		VeSceneRenderable* pkIter = m_kRenderableList.GetIterNode()->m_tContent;
		VE_ASSERT(pkIter);
		m_kRenderableList.Next();
		VeSceneRenderable2D* pkRenderable2D = VeDynamicCast(VeSceneRenderable2D, pkIter);
		if(pkRenderable2D)
		{
			pkRenderable2D->UpdateNodeData(m_kDerivedTransform, m_kDerivedMulColor, m_kDerivedAddColor, m_u32UpdateFrame);
		}
		pkIter->Visit(kQueue, m_u32VisibleMask);
	}
	BeginChild();
	VeSceneNode* pkIter = NextChild();
	while(pkIter)
	{
		if(pkIter->GetVisibleMask())
		{
			pkIter->Visit(kQueue);
		}
		pkIter = NextChild();
	}
	EndChild();
}
//--------------------------------------------------------------------------
void VeSceneNode2D::BeginChild()
{
	m_kIter = m_kZOrderMap.Begin();
	VeRefList<VeSceneNode*>* pkList = m_kIter->m_tFirst ? m_kZOrderChildren[m_kIter->m_tSecond] : &m_kChildren;
	pkList->BeginIterator();
}
//--------------------------------------------------------------------------
VeSceneNode* VeSceneNode2D::NextChild()
{
	VeSceneNode* pkRes(NULL);
	while((!pkRes) && m_kIter != m_kZOrderMap.End())
	{
		VeRefList<VeSceneNode*>* pkList = m_kIter->m_tFirst ? m_kZOrderChildren[m_kIter->m_tSecond] : &m_kChildren;
		if(pkList->IsEnd())
		{
			if((++m_kIter) != m_kZOrderMap.End())
			{
				pkList = m_kIter->m_tFirst ? m_kZOrderChildren[m_kIter->m_tSecond] : &m_kChildren;
				pkList->BeginIterator();
			}
		}
		else
		{
			pkRes = pkList->GetIterNode()->m_tContent;
			pkList->Next();
		}
	}
	return pkRes;
}
//--------------------------------------------------------------------------
void VeSceneNode2D::BeginChildR()
{
	m_kIter = m_kZOrderMap.Last();
	VeRefList<VeSceneNode*>* pkList = m_kIter->m_tFirst ? m_kZOrderChildren[m_kIter->m_tSecond] : &m_kChildren;
	pkList->BeginIteratorFromLast();
}
//--------------------------------------------------------------------------
VeSceneNode* VeSceneNode2D::NextChildR()
{
	VeSceneNode* pkRes(NULL);
	while((!pkRes) && m_kIter != m_kZOrderMap.End())
	{
		VeRefList<VeSceneNode*>* pkList = m_kIter->m_tFirst ? m_kZOrderChildren[m_kIter->m_tSecond] : &m_kChildren;
		if(pkList->IsEnd())
		{
			if((--m_kIter) != m_kZOrderMap.End())
			{
				pkList = m_kIter->m_tFirst ? m_kZOrderChildren[m_kIter->m_tSecond] : &m_kChildren;
				pkList->BeginIteratorFromLast();
			}
		}
		else
		{
			pkRes = pkList->GetIterNode()->m_tContent;
			pkList->Pre();
		}
	}
	return pkRes;
}
//--------------------------------------------------------------------------
void VeSceneNode2D::EndChild()
{
	m_kIter = m_kZOrderMap.End();
	for(VeUInt32 i(0); i < m_kZOrderChildren.Size(); ++i)
	{
		m_kZOrderChildren[i]->EndIterator();
	}
	m_kChildren.EndIterator();
}
//--------------------------------------------------------------------------
void VeSceneNode2D::UpdateFromParent()
{
	VeSceneNode2D* pkParent = VeDynamicCast(VeSceneNode2D, m_pkParent);
	if(pkParent)
	{
		pkParent->UpdateFromParent();
		if(m_bDirty || (pkParent->m_u32UpdateFrame > m_u32UpdateFrame))
		{
			m_kDerivedTransform.Concat(VeTransform2D(m_kPosition, m_kSkew, m_kScale), pkParent->m_kDerivedTransform);
			m_kDerivedMulColor = m_kMulColor * pkParent->m_kDerivedMulColor;
			m_kDerivedAddColor = m_kAddColor + pkParent->m_kDerivedAddColor;
			m_u32UpdateFrame = g_pRenderFrameManager->GetFrameCount();
			m_bDirty = false;
		}
	}
	else if(m_bDirty)
	{
		m_kDerivedTransform.Set(m_kPosition, m_kSkew, m_kScale);
		m_kDerivedMulColor = m_kMulColor;
		m_kDerivedAddColor = m_kAddColor;
		m_u32UpdateFrame = g_pRenderFrameManager->GetFrameCount();
		m_bDirty = false;
	}
}
//--------------------------------------------------------------------------
void VeSceneNode2D::UpdateContext(VeRenderNode* pkContext)
{
	m_pkContext = m_pkRenderNode ? m_pkRenderNode : pkContext;
	{
		BeginChild();
		VeSceneNode2D* pkIter = NextChildByType<VeSceneNode2D>();
		while(pkIter)
		{
			pkIter->UpdateContext(m_pkContext);
			pkIter = NextChildByType<VeSceneNode2D>();
		}
		EndChild();
	}
	{
		BeginRenderable();
		VeSceneRenderable2D* pkIter = NextRenderableByType<VeSceneRenderable2D>();
		while(pkIter)
		{
			pkIter->m_pkRenderNode->SetParent(m_pkContext);
			pkIter = NextRenderableByType<VeSceneRenderable2D>();
		}
		EndRenderable();
	}
}
//--------------------------------------------------------------------------
void VeSceneNode2D::UpdateContext()
{
	VeSceneNode2D* pkParent = VeDynamicCast(VeSceneNode2D, m_pkParent);
	m_pkContext = m_pkRenderNode ? m_pkRenderNode : (pkParent ? pkParent->m_pkContext : NULL);
	if(m_pkContext)
	{
		{
			BeginChild();
			VeSceneNode2D* pkIter = NextChildByType<VeSceneNode2D>();
			while(pkIter)
			{
				pkIter->UpdateContext(m_pkContext);
				pkIter = NextChildByType<VeSceneNode2D>();
			}
			EndChild();
		}
		{
			BeginRenderable();
			VeSceneRenderable2D* pkIter = NextRenderableByType<VeSceneRenderable2D>();
			while(pkIter)
			{
				pkIter->m_pkRenderNode->SetParent(m_pkContext);
				pkIter = NextRenderableByType<VeSceneRenderable2D>();
			}
			EndRenderable();
		}
	}
}
//--------------------------------------------------------------------------
void VeSceneNode2D::UpdateZOrder(VeFloat32 f32ZOrder)
{
	VE_ASSERT(m_f32ZOrder != f32ZOrder);
	VeSceneNode2D* pkParent = VeDynamicCast(VeSceneNode2D, m_pkParent);
	if(pkParent)
	{
		if(m_f32ZOrder && (m_kNode.GetRefList()->Size() == 1))
		{
			VeMap<VeFloat32, VeUInt32>::iterator itFind = pkParent->m_kZOrderMap.Find(m_f32ZOrder);
			VE_ASSERT(itFind != pkParent->m_kZOrderMap.End() && itFind->m_tSecond < pkParent->m_kZOrderChildren.Size());
			VeUInt32 u32Index(itFind->m_tSecond);
			VeRefList<VeSceneNode*>* pkList = pkParent->m_kZOrderChildren[u32Index];
			VE_ASSERT(m_kNode.IsAttach(*pkList));
			m_kNode.Detach();
			VE_ASSERT(pkList->Empty());
			pkParent->m_kZOrderMap.Erase(itFind);
			DestoryNodeList(pkList);
			if(u32Index < (pkParent->m_kZOrderChildren.Size() - 1))
			{
				pkParent->m_kZOrderChildren[u32Index] = pkParent->m_kZOrderChildren.Back();
				VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, pkParent->m_kZOrderChildren.Back()->GetHeadNode()->m_tContent);
				pkParent->m_kZOrderMap[pkNode->m_f32ZOrder] = u32Index;
			}
			pkParent->m_kZOrderChildren.PopBack();
			VE_ASSERT(pkParent->m_kZOrderMap.Size() == (pkParent->m_kZOrderChildren.Size() + 1));
		}
		else
		{
			m_kNode.Detach();
		}
		if(f32ZOrder)
		{
			VeMap<VeFloat32, VeUInt32>::iterator itFind = pkParent->m_kZOrderMap.Find(f32ZOrder);
			if(itFind != pkParent->m_kZOrderMap.End())
			{
				VE_ASSERT(itFind->m_tSecond < pkParent->m_kZOrderChildren.Size());
				pkParent->m_kZOrderChildren[itFind->m_tSecond]->AttachBack(m_kNode);
			}
			else
			{
				pkParent->m_kZOrderMap[f32ZOrder] = pkParent->m_kZOrderChildren.Size();
				pkParent->m_kZOrderChildren.Increase();
				pkParent->m_kZOrderChildren.Back() = CreateNodeList();
				pkParent->m_kZOrderChildren.Back()->AttachBack(m_kNode);
			}
		}
		else
		{
			pkParent->m_kChildren.AttachBack(m_kNode);
		}
	}
	m_f32ZOrder = f32ZOrder;
}
//--------------------------------------------------------------------------
VeRefList<VeSceneNode*>* VeSceneNode2D::CreateNodeList()
{
	return new(VePoolMalloc(VePoolAllocator::GetPoolAllocator(sizeof(VeRefList<VeSceneNode*>))))
		VeRefList<VeSceneNode*>();
}
//--------------------------------------------------------------------------
void VeSceneNode2D::DestoryNodeList(VeRefList<VeSceneNode*>* pkList)
{
	VE_ASSERT(pkList);
	pkList->~VeRefList<VeSceneNode*>();
	VePoolFree(VePoolAllocator::GetPoolAllocator(sizeof(VeRefList<VeSceneNode*>)), pkList);
}
//--------------------------------------------------------------------------
void VeSceneNode2D::From(VeBinaryIStream& kIn)
{
	kIn >> m_u32VisibleMask;
	kIn >> m_f32ZOrder;
}
//--------------------------------------------------------------------------
void VeSceneNode2D::To(VeBinaryOStream& kOut) const
{
	kOut << m_u32VisibleMask;
	kOut << m_f32ZOrder;
}
//--------------------------------------------------------------------------
void VeSceneNode2D::From(VeXMLElement* pkElement)
{
	VeSceneNode::From(pkElement);
	m_f32ZOrder = pkElement->Attribute("z", 0.0f);
	m_kPosition.x = g_pLua->GetExpression(pkElement->Attribute("x"), 0.0f);
	m_kPosition.y = g_pLua->GetExpression(pkElement->Attribute("y"), 0.0f);
	VeFloat32 f32Rot = g_pLua->GetExpression(pkElement->Attribute("rot"), 0.0f);
	m_kSkew.x = g_pLua->GetExpression(pkElement->Attribute("skx"), f32Rot);
	m_kSkew.y = g_pLua->GetExpression(pkElement->Attribute("sky"), f32Rot);
	VeFloat32 f32Scale = g_pLua->GetExpression(pkElement->Attribute("s"), 1.0f);
	m_kScale.x = g_pLua->GetExpression(pkElement->Attribute("scx"), f32Scale);
	m_kScale.y = g_pLua->GetExpression(pkElement->Attribute("scy"), f32Scale);
	m_kMulColor = pkElement->Attribute("mul", VeColor::WHITE);
	m_kAddColor = pkElement->Attribute("add", VeColor::ZERO);
}
//--------------------------------------------------------------------------
const VeTransform2D& VeSceneNode2D::GetDerivedTransform()
{
	UpdateActions();
	UpdateFromParent();
	return m_kDerivedTransform;
}
//--------------------------------------------------------------------------
void VeSceneNode2D::SetDerivedTransform(const VeTransform2D& kTransform)
{
	VeSceneNode2D* pkParent = VeDynamicCast(VeSceneNode2D, m_pkParent);
	if(!pkParent)
	{
		m_kDerivedTransform = kTransform;
		m_kDerivedMulColor = m_kMulColor;
		m_kDerivedAddColor = m_kAddColor;
		m_u32UpdateFrame = 0xFFFFFFFF;
		m_bDirty = false;
	}
}
//--------------------------------------------------------------------------
void VeSceneNode2D::NotifyRefresh()
{
	VeSceneNode2D* pkParent = VeDynamicCast(VeSceneNode2D, m_pkParent);
	if(pkParent)
	{
		m_bDirty = true;
	}
	else
	{
		m_kDerivedTransform.Set(m_kPosition, m_kSkew, m_kScale);
		m_kDerivedMulColor = m_kMulColor;
		m_kDerivedAddColor = m_kAddColor;
		m_u32UpdateFrame = g_pRenderFrameManager->GetFrameCount();
		m_bDirty = false;
	}
	BeginChild();
	VeSceneNode2D* pkIter = NextChildByType<VeSceneNode2D>();
	while(pkIter)
	{
		pkIter->NotifyRefresh();
		pkIter = NextChildByType<VeSceneNode2D>();
	}
	EndChild();
}
//--------------------------------------------------------------------------
VeRenderNode* VeSceneNode2D::GetDraw2DRoot()
{
	return g_pSceneManager->m_pkDraw2DRoot;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSceneNode2D)
{
	Module() [
		Class< VeSceneNode2D, Base<VeSceneNode> >().
			Def(ConstructorNew<void>()).
			Def("SetPosition", (void (VeSceneNode2D::*)(VeFloat32,VeFloat32))&VeSceneNode2D::SetPosition).
			Def("SetPosition", (void (VeSceneNode2D::*)(const VeVector2D&))&VeSceneNode2D::SetPosition).
			Def("SetPositionX", &VeSceneNode2D::SetPositionX).
			Def("SetPositionY", &VeSceneNode2D::SetPositionY).
			Def("GetPosition", &VeSceneNode2D::GetPosition).
			Def("GetPositionX", &VeSceneNode2D::GetPositionX).
			Def("GetPositionY", &VeSceneNode2D::GetPositionY).
			Def("SetScale", (void (VeSceneNode2D::*)(VeFloat32))&VeSceneNode2D::SetScale).
			Def("SetScale", (void (VeSceneNode2D::*)(VeFloat32,VeFloat32))&VeSceneNode2D::SetScale).
			Def("SetScale", (void (VeSceneNode2D::*)(const VeVector2D&))&VeSceneNode2D::SetScale).
			Def("SetScaleX", &VeSceneNode2D::SetScaleX).
			Def("SetScaleY", &VeSceneNode2D::SetScaleY).
			Def("GetScale", &VeSceneNode2D::GetScale).
			Def("SetRotate", &VeSceneNode2D::SetRotate).
			Def("SetSkew", (void (VeSceneNode2D::*)(VeFloat32,VeFloat32))&VeSceneNode2D::SetSkew).
			Def("SetSkew", (void (VeSceneNode2D::*)(const VeVector2D&))&VeSceneNode2D::SetSkew).
			Def("GetRotate", &VeSceneNode2D::GetRotate).
			Def("GetSkew", &VeSceneNode2D::GetSkew).
			Def("SetMulColor", (void (VeSceneNode2D::*)(VeFloat32,VeFloat32,VeFloat32,VeFloat32))&VeSceneNode2D::SetMulColor).
			Def("SetMulColor", (void (VeSceneNode2D::*)(const VeColor&))&VeSceneNode2D::SetMulColor).
			Def("GetMulColor", &VeSceneNode2D::GetMulColor).
			Def("SetAddColor", (void (VeSceneNode2D::*)(VeFloat32,VeFloat32,VeFloat32,VeFloat32))&VeSceneNode2D::SetAddColor).
			Def("SetAddColor", (void (VeSceneNode2D::*)(const VeColor&))&VeSceneNode2D::SetAddColor).
			Def("GetAddColor", &VeSceneNode2D::GetAddColor).
			Def("SetZOrder", &VeSceneNode2D::SetZOrder).
			Def("GetZOrder", &VeSceneNode2D::GetZOrder)
	];
}
//--------------------------------------------------------------------------
