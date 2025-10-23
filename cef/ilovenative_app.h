// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights reserved
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
// Refactored by Sarthak Kapila (sarthakkapila1@gmail.com) 2025.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"

// Implement application-level callbacks for the browser process.
class ILOVENATIVE_app : public CefApp, public CefBrowserProcessHandler {
 public:
  ILOVENATIVE_app();

  // CefApp methods:
  CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
    return this;
  }

  // CefBrowserProcessHandler methods:
  void OnContextInitialized() override;
  CefRefPtr<CefClient> GetDefaultClient() override;

 private:
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(ILOVENATIVE_app);
};

#endif
