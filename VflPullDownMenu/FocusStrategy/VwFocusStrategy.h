/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :                               RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :  VistaWidgets                 RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :  VistaWidgets                   Rheinisch-Westfaelische    */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  2012-2013   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
/*                                                                            */
/*    THIS SOFTWARE IS PROVIDED 'AS IS'. ANY WARRANTIES ARE DISCLAIMED. IN    */
/*    NO CASE SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DAMAGES.    */
/*    REDISTRIBUTION AND USE OF THE NON MODIFIED TOOLKIT IS PERMITTED. OWN    */
/*    DEVELOPMENTS BASED ON THIS TOOLKIT MUST BE CLEARLY DECLARED AS SUCH.    */
/*                                                                            */
/*============================================================================*/

//#ifndef _VwFocusStrategy_H
//#define _VwFocusStrategy_H

/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/

#include"../VglConfig.h"
#include "VistaWidgets/VwFocusStrategy.h"
#include "VistaWidgets/VwInputSlot.h"


#include"VwHandleSignal.h"

#include "VistaWidgets/Aspects/VwAspects.h"
#include <VistaBase/VistaVectorMath.h>

#include <map>
/*============================================================================*/
/* FORWARD DECLARATIONS                                                       */
/*============================================================================*/
class VwHandleInfo;
class VwPlaneHandleInfo;

/*============================================================================*/
/* CLASS DEFINITIONS                                                          */
/*============================================================================*/
/**
 * @brief	This focus strategy gives focus depending depending on the distance 
 *			of the virtual device to the surface of a widget.
 * @details	If a virtual device is inside a widget the distance to the widget 
 *			is 0.0.
 *			It uses either a position or a pose to determine the focus.
 *			If no position or pose was set this strategy focuses nothing.
 */
class VGLWAPI  VwFocusStrategy: public IVwFocusStrategy {
	public:
	VwFocusStrategy();
	virtual ~VwFocusStrategy();

	/**
	 * @copydoc	IVwFocusStrategy::EvaluateFocus
	 */
	virtual const FocusResultVector& EvaluateFocus();

	/**
	 * @brief	Returns the radius around the virtual device in which focus is
	 *			considered.
	 */
	float GetSelectionRadius() const;
	/**
	 * @brief	Sets the radius around the virtual device in which focus is
	 *			considered.
	 */
	void SetSelectionRadius( const float& oValue );


	float GetFocusRadius() const;
	/**
	* @brief	Sets the radius around the virtual device in which focus is
	*			considered.
	*/
	void SetFocusRadius( const float& oValue );
	void LockedStrategy() { m_bLocked = true; }
	/**
	 * @brief	Returns the input slot representing a position.
	 */
	VwInputSlot<VistaVector3D>* GetPositionInputSlot() const;
	/**
	 * @brief	Sets the input slot representing a position.
	 * @param	pSlot the input slot used as the position for the evaluation of
	 *			the foci.
	 * @pre		@p pSlot can be any valid @p VwInputSlot<VistaVector3D> or @p nullptr.
	 * @remark	Setting a position input slots resets the pose input slot to nullptr.
	 */
	void SetPositionInputSlot( VwInputSlot<VistaVector3D>* pSlot );
	/**
	 * @brief	Returns the input slot representing a pose.
	 */
	VwInputSlot<VistaTransformMatrix>* GetPoseInputSlot() const;
	/**
	* @brief	Sets the input slot representing a pose.
	* @param	pValue the input slot used as the pose for the evaluation of
	*			the foci.
	* @pre		@p pSlot can be any valid @p VwInputSlot<VistaTransformMatrix> or @p nullptr.
	* @remark	Setting a pose input slots resets the pose input slot to nullptr.
	*/
	void SetPoseInputSlot( VwInputSlot<VistaTransformMatrix>* pValue );


	/**
	* @brief	Returns the input slot representing a pose.
	*/
	VwInputSlot<bool>* GetSelectInputSlot() const;
	/**
	* @brief	Sets the input slot representing a pose.
	* @param	pValue the input slot used as the pose for the evaluation of
	*			the foci.
	* @pre		@p pSlot can be any valid @p VwInputSlot<VistaTransformMatrix> or @p nullptr.
	* @remark	Setting a pose input slots resets the pose input slot to nullptr.
	*/
	void SetSelectInputSlot( VwInputSlot<bool>* pValue );

	virtual std::vector<VwFocusHandle*> GetRegisteredFocusHandles() const override;


	VwHandleSignal&  GetClickSignal( );
	VwHandleSignal&  GetButtonDownSignal();
	VwHandleSignal&  GetButtonUpSignal();
	protected:
	virtual bool DoRegistration( VwFocusHandle* pHandle ) override;
	virtual bool DoUnRegistration( VwFocusHandle* pHandle ) override;

	private:
	class CompareHandles;
	void DeleteResultAspects( VwRayAspect* pGroup );

	private:


	VwHandleSignal                     m_sigClick;
	VwHandleSignal                     m_sigButtonUp;
	VwHandleSignal                     m_sigButtonDown;

	VwInputSlot<VistaTransformMatrix>* m_pPoseInputSlot;
	VwInputSlot<bool>*                 m_pSelectInputSlot;
	using HandleInfoContainer = std::vector<VwHandleInfo*>;
	HandleInfoContainer m_vecHandleInfos;
	IVwFocusStrategy::FocusResultVector m_vecFocusedFocusHandles;
	IVwFocusStrategy::FocusResultVector m_vecClickedHandles;


	std::map<VwFocusHandle*, std::shared_ptr<VwRayAspect> > m_mapResultAspects;

	bool       m_bClickState;
	bool     m_bLocked;
	float m_pSelectionRadius;
	float m_fFocusRadius;
};

//#endif // _VwFocusStrategy_H
