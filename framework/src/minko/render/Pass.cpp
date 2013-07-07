/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Pass.hpp"

using namespace minko::render;

Pass::Pass(const std::string&				name,
		   std::shared_ptr<render::Program>	program,
		   BindingMap&						attributeBindings,
		   BindingMap&						uniformBindings,
		   BindingMap&						stateBindings,
		   const float						priority,
		   Blending::Source					blendingSourceFactor,
		   Blending::Destination			blendingDestinationFactor,
		   bool								depthMask,
		   CompareMode						depthFunc) :
	_name(name),
	_program(program),
	_attributeBindings(attributeBindings),
	_uniformBindings(uniformBindings),
	_stateBindings(stateBindings),
	_priority(priority),
	_blendingSourceFactor(blendingSourceFactor),
	_blendingDestinationFactor(blendingDestinationFactor),
	_depthMask(depthMask),
	_depthFunc(depthFunc)
{
}