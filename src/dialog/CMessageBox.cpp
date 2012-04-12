/*
 * CMessageBox.cpp
 *
 *  Created on: 04.12.2009
 *      Author: gerstrong
 */

#include "CMessageBox.h"
#include "sdl/CVideoDriver.h"
#include "sdl/input/CInput.h"
#include "graphics/CGfxEngine.h"
#include "StringUtils.h"

// This is a local functor that is invoked when the dialog has be closed
struct CloseDialog : public InvokeFunctorEvent
{
	CloseDialog(bool &mustClose) : mMustClose(mustClose) {}

	void operator()()
	{		mMustClose = true;	}

	bool &mMustClose;
};

CMessageBox::CMessageBox(const std::string& Text, bool lower, bool keymsg, bool leftbound) :
CGUIDialog(CRect<float>(0.1f, 0.1f, 0.8f, 0.8f)),
m_mustclose(false)
{
	const char closeChar = 0x1F;
	std::string closeString;
	closeString = closeChar;
	CGUIButton*	pButton	= new CGUIButton( closeString, new CloseDialog(m_mustclose), CGUIButton::NONE );

	addControl( pButton, CRect<float>(0.0f, 0.0f, 0.06f/0.8f, 0.06f/0.8f) );

	mpReturnButton = pButton;

	setBackground( CGUIDialog::VORTICON );

	mpTextCtrl = new CGUIText( Text );

	// Those formulas work well with our constellation but I don't think they are perfect.
	// They transform the Message Box the way the text fits perfectly in.
	mRect.w = (mpTextCtrl->mTextDim.w+2)*0.028f;
	mRect.h = (mpTextCtrl->mTextDim.h+2)*0.05f;
	mRect.x = (1.0f - mRect.w)/2.0f;
	mRect.y = (1.0f - mRect.h)/2.0f;

	// now let's center the long text...
	CRect<float> TextRect;
	TextRect.x = 0.055f/mRect.w;
	TextRect.y = 0.05f/mRect.h;
	TextRect.w = 0.9f;
	TextRect.h = 0.9f;

	addControl( mpTextCtrl, TextRect );

	CRect<float> closeRect = pButton->mRect;
	closeRect.x = mRect.x;
	closeRect.y = mRect.y;
	pButton->setRect(closeRect);
}

void CMessageBox::processLogic()
{
	// TODO: Here we need to process the close logic, The (X) already work, but command must be caught here!

	CGUIDialog::processLogic();
}

bool CMessageBox::isFinished()
{ return m_mustclose; }
