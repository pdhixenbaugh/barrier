/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2002 Chris Schoeneman
 * 
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file COPYING that should have accompanied this file.
 * 
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef CPRIMARYCLIENT_H
#define CPRIMARYCLIENT_H

#include "IClient.h"
#include "ProtocolTypes.h"

class CScreen;

//! Primary screen as pseudo-client
/*!
The primary screen does not have a client associated with it.  This
class provides a pseudo-client to allow the primary screen to be
treated as if it was a client.
*/
class CPrimaryClient : public IClient {
public:
	/*!
	\c name is the name of the server and \p screen is primary screen.
	*/
	CPrimaryClient(const CString& name, CScreen* screen);
	~CPrimaryClient();

	//! @name manipulators
	//@{

	//! Update configuration
	/*!
	Handles reconfiguration of jump zones.
	*/
	void				reconfigure(UInt32 activeSides);

	//@}
	//! @name accessors
	//@{

	//! Get cursor center position
	/*!
	Return the cursor center position which is where we park the
	cursor to compute cursor motion deltas and should be far from
	the edges of the screen, typically the center.
	*/
	void				getCursorCenter(SInt32& x, SInt32& y) const;

	//! Get toggle key state
	/*!
	Returns the primary screen's current toggle modifier key state.
	*/
	KeyModifierMask		getToggleMask() const;

	//! Get screen lock state
	/*!
	Returns true if the user is locked to the screen.
	*/
	bool				isLockedToScreen() const;

	//@}

	// FIXME -- these probably belong on IScreen
	virtual void		enable();
	virtual void		disable();

	// IScreen overrides
	virtual void*		getEventTarget() const;
	virtual bool		getClipboard(ClipboardID id, IClipboard*) const;
	virtual SInt32		getJumpZoneSize() const;
	virtual void		getShape(SInt32& x, SInt32& y,
							SInt32& width, SInt32& height) const;
	virtual void		getCursorPos(SInt32& x, SInt32& y) const;

	// IClient overrides
	virtual void		enter(SInt32 xAbs, SInt32 yAbs,
							UInt32 seqNum, KeyModifierMask mask,
							bool forScreensaver);
	virtual bool		leave();
	virtual void		setClipboard(ClipboardID, const CString&);
	virtual void		grabClipboard(ClipboardID);
	virtual void		setClipboardDirty(ClipboardID, bool);
	virtual void		keyDown(KeyID, KeyModifierMask, KeyButton);
	virtual void		keyRepeat(KeyID, KeyModifierMask,
							SInt32 count, KeyButton);
	virtual void		keyUp(KeyID, KeyModifierMask, KeyButton);
	virtual void		mouseDown(ButtonID);
	virtual void		mouseUp(ButtonID);
	virtual void		mouseMove(SInt32 xAbs, SInt32 yAbs);
	virtual void		mouseWheel(SInt32 delta);
	virtual void		screensaver(bool activate);
	virtual void		resetOptions();
	virtual void		setOptions(const COptionsList& options);
	virtual CString		getName() const;

private:
	CString				m_name;
	CScreen*			m_screen;
	bool				m_clipboardDirty[kClipboardEnd];
};

#endif
