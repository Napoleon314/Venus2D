////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneNode.h
//  Version:     v1.00
//  Created:     11/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeRenderQueue;
VeSmartPointer(VeAction);
VeSmartPointer(VeFiniteTimeAction);

class VE_MAIN_API VeSceneNode : public VeObject
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSceneNode);
public:
	VeSceneNode();

	virtual ~VeSceneNode();

	VE_INLINE void SetVisibleMask(VeUInt32 u32Mask);

	VE_INLINE VeUInt32 GetVisibleMask();

	VE_INLINE VeSceneNode* GetParent();

	virtual void AttachChild(VeSceneNode* pkChild);

	virtual void DetachFromParent();

	virtual void DetachAllChildren();

	virtual void AttachRenderable(VeSceneRenderable* pkRenderable);

	virtual void DetachRenderable(VeSceneRenderable* pkRenderable);

	virtual void DetachAllRenderables();

	virtual void Visit(VeRenderQueue& kQueue);

	virtual void BeginChild();

	virtual VeSceneNode* NextChild();

	virtual void BeginChildR();

	virtual VeSceneNode* NextChildR();

	virtual void EndChild();

	virtual void BeginRenderable();

	virtual VeSceneRenderable* NextRenderable();

	virtual void BeginRenderableR();

	virtual VeSceneRenderable* NextRenderableR();

	virtual void EndRenderable();

	void RunAction(VeAction* pkAction);

	void StopAllActions();

	void StopAction(VeAction* pkAction);

	bool HasRunningAction();

	void UpdateActions();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	template<class T>
	T* NextChildByType()
	{
		T* pkRes(NULL);
		while(!pkRes)
		{
			VeSceneNode* pkIter = NextChild();
			if(pkIter)
			{
				pkRes = VeDynamicCast(T, pkIter);
			}
			else
			{
				break;
			}
		}
		return pkRes;
	}

	template<class T>
	T* NextChildByTypeR()
	{
		T* pkRes(NULL);
		while(!pkRes)
		{
			VeSceneNode* pkIter = NextChildR();
			if(pkIter)
			{
				pkRes = VeDynamicCast(T, pkIter);
			}
			else
			{
				break;
			}
		}
		return pkRes;
	}

	template<class T>
	T* NextRenderableByType()
	{
		T* pkRes(NULL);
		while(!pkRes)
		{
			VeSceneRenderable* pkIter = NextRenderable();
			if(pkIter)
			{
				pkRes = VeDynamicCast(T, pkIter);
			}
			else
			{
				break;
			}
		}
		return pkRes;
	}

	template<class T>
	T* NextRenderableByTypeR()
	{
		T* pkRes(NULL);
		while(!pkRes)
		{
			VeSceneRenderable* pkIter = NextRenderableR();
			if(pkIter)
			{
				pkRes = VeDynamicCast(T, pkIter);
			}
			else
			{
				break;
			}
		}
		return pkRes;
	}

protected:
	void RunAction_S(lua_State* pkState, VeFiniteTimeAction* pkAction);

	VeLuaSyncHolder* RunAction_A(lua_State* pkState, VeFiniteTimeAction* pkAction);

	VeUInt32 m_u32VisibleMask;
	VeRefNode<VeSceneNode*> m_kNode;
	VeSceneNode* m_pkParent;
	VeRefList<VeSceneNode*> m_kChildren;
	VeRefList<VeSceneRenderable*> m_kRenderableList;
	VeRefList<VeAction*> m_kActionList;
	VeUInt32 m_u32ActionUpdateFrame;

};

VeSmartPointer(VeSceneNode);

class VE_MAIN_API VeSceneNode2D : public VeSceneNode
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSceneNode2D);
public:
	VeSceneNode2D();

	virtual ~VeSceneNode2D();

	VE_INLINE void SetPosition(VeFloat32 x, VeFloat32 y);

	VE_INLINE void SetPosition(const VeVector2D& kPos);

	VE_INLINE void SetPositionX(VeFloat32 x);

	VE_INLINE void SetPositionY(VeFloat32 y);

	VE_INLINE const VeVector2D& GetPosition();

	VE_INLINE VeFloat32 GetPositionX();

	VE_INLINE VeFloat32 GetPositionY();

	VE_INLINE void SetScale(VeFloat32 f32Scale);

	VE_INLINE void SetScale(VeFloat32 x, VeFloat32 y);

	VE_INLINE void SetScale(const VeVector2D& kScale);

	VE_INLINE void SetScaleX(VeFloat32 f32ScaleX);

	VE_INLINE void SetScaleY(VeFloat32 f32ScaleY);

	VE_INLINE const VeVector2D& GetScale();

	VE_INLINE void SetRotate(VeFloat32 f32Rotate);

	VE_INLINE void SetSkew(VeFloat32 x, VeFloat32 y);

	VE_INLINE void SetSkew(const VeVector2D& kSkew);

	VE_INLINE VeFloat32 GetRotate();

	VE_INLINE const VeVector2D& GetSkew();

	VE_INLINE void SetMulColor(VeFloat32 r, VeFloat32 g, VeFloat32 b, VeFloat32 a);

	VE_INLINE void SetMulColor(const VeColor& kColor);

	VE_INLINE const VeColor& GetMulColor();

	VE_INLINE void SetAddColor(VeFloat32 r, VeFloat32 g, VeFloat32 b, VeFloat32 a = 0.0f);

	VE_INLINE void SetAddColor(const VeColor& kColor);

	VE_INLINE const VeColor& GetAddColor();

	VE_INLINE void SetZOrder(VeFloat32 f32ZOrder);

	VE_INLINE VeFloat32 GetZOrder();

	virtual void AttachChild(VeSceneNode* pkChild);

	virtual void DetachFromParent();

	virtual void DetachAllChildren();

	virtual void AttachRenderable(VeSceneRenderable* pkRenderable);

	virtual void DetachRenderable(VeSceneRenderable* pkRenderable);

	virtual void Visit(VeRenderQueue& kQueue);

	virtual void BeginChild();

	virtual VeSceneNode* NextChild();

	virtual void BeginChildR();

	virtual VeSceneNode* NextChildR();

	virtual void EndChild();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	const VeTransform2D& GetDerivedTransform();

	void SetDerivedTransform(const VeTransform2D& kTransform);

	void NotifyRefresh();

	void UpdateContext(VeRenderNode* pkContext);

protected:
	friend class VeUIManager;

	void UpdateFromParent();	

	void UpdateContext();

	void UpdateZOrder(VeFloat32 f32ZOrder);

	static VeRefList<VeSceneNode*>* CreateNodeList();

	static void DestoryNodeList(VeRefList<VeSceneNode*>* pkList);

	static VeRenderNode* GetDraw2DRoot();

	VeFloat32 m_f32ZOrder;
	VeMap<VeFloat32, VeUInt32> m_kZOrderMap;
	VeMap<VeFloat32, VeUInt32>::iterator m_kIter;
	VeVector< VeRefList<VeSceneNode*>* > m_kZOrderChildren;
	VeRenderNode* m_pkRenderNode;
	VeRenderNode* m_pkContext;
	VeVector2D m_kPosition;
	VeVector2D m_kSkew;
	VeVector2D m_kScale;
	VeColor m_kMulColor;
	VeColor m_kAddColor;
	VeTransform2D m_kDerivedTransform;
	VeColor m_kDerivedMulColor;
	VeColor m_kDerivedAddColor;
	VeUInt32 m_u32UpdateFrame;
	bool m_bDirty;

};

VeSmartPointer(VeSceneNode2D);

#ifndef VE_NO_INLINE
#	include "VeSceneNode.inl"
#endif
