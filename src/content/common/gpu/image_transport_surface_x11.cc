// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/common/gpu/image_transport_surface.h"

namespace content {

// static
scoped_refptr<gfx::GLSurface> ImageTransportSurface::CreateNativeSurface(
    GpuChannelManager* manager,
    GpuCommandBufferStub* stub,
    const gfx::GLSurfaceHandle& handle) {
  DCHECK(handle.handle);
  DCHECK(handle.transport_type == gfx::NATIVE_DIRECT ||
         handle.transport_type == gfx::NATIVE_TRANSPORT);
  scoped_refptr<gfx::GLSurface> surface =
      gfx::GLSurface::CreateViewGLSurface(false, handle.handle);
  if (!surface.get())
    return surface;
  return scoped_refptr<gfx::GLSurface>(new PassThroughImageTransportSurface(
      manager, stub, surface.get(), handle.is_transport()));
}

}  // namespace content
