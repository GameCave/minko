/*
Copyright (c) 2014 Aerys

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

#pragma once

#include "minko/Common.hpp"
#include "minko/component/AbstractLodScheduler.hpp"

namespace minko
{
    namespace component
    {
        class TextureLodScheduler :
            public AbstractLodScheduler
        {
        public:
            typedef std::shared_ptr<TextureLodScheduler>    Ptr;

        private:
            typedef std::shared_ptr<scene::Node>                NodePtr;

            typedef std::shared_ptr<SceneManager>               SceneManagerPtr;
            typedef std::shared_ptr<Surface>                    SurfacePtr;

            typedef std::shared_ptr<data::Provider>             ProviderPtr;

            typedef std::shared_ptr<material::Material>         MaterialPtr;
            
            typedef std::shared_ptr<render::AbstractTexture>    AbstractTexturePtr;

            typedef std::shared_ptr<file::AssetLibrary>         AssetLibraryPtr;

            struct TextureResourceInfo
            {
                ResourceInfo*                                   base;

                AbstractTexturePtr                              texture;
                std::string                                     textureName;

                std::unordered_set<MaterialPtr>                 materials;
                std::unordered_map<SurfacePtr, int>             surfaceToActiveLodMap;

                std::unordered_map<
                    NodePtr,
                    Signal<data::Store&, ProviderPtr, const data::Provider::PropertyName&>::Slot
                >                                               modelToWorldMatrixChangedSlots;
            };

        private:
            SceneManagerPtr                                             _sceneManager;

            std::unordered_map<std::string, TextureResourceInfo>        _textureResources;

            math::vec3                                                  _eyePosition;
            float                                                       _fov;
            float                                                       _aspectRatio;

            math::vec4                                                  _viewport;

            AssetLibraryPtr                                             _assetLibrary;

        public:
            inline
            static
            Ptr
            create(AssetLibraryPtr assetLibrary)
            {
                auto instance = Ptr(new TextureLodScheduler(assetLibrary));

                return instance;
            }

        protected:
            void
            sceneManagerSet(SceneManagerPtr sceneManager);

            void
            surfaceAdded(SurfacePtr surface);

            void
            viewPropertyChanged(const math::mat4&   worldToScreenMatrix,
                                const math::mat4&   viewMatrix,
                                const math::vec3&   eyePosition,
                                float               fov,
                                float               aspectRatio,
                                float               zNear,
                                float               zFar);

            void
            viewportChanged(const math::vec4& viewport);

            void
            maxAvailableLodChanged(ResourceInfo&    resource,
                                   int              maxAvailableLod);

            LodInfo
            lodInfo(ResourceInfo&   resource,
                    float           time);

        private:
            TextureLodScheduler(AssetLibraryPtr assetLibrary);

            void
            activeLodChanged(TextureResourceInfo&   resource,
                             SurfacePtr             surface,
                             int                    previousLod,
                             int                    lod);

            int
            computeRequiredLod(const TextureResourceInfo& resource,
                               SurfacePtr                 surface);

            float
            computeLodPriority(const TextureResourceInfo&  resource,
                               SurfacePtr                  surface,
                               int                         requiredLod,
                               int                         activeLod,
                               float                       time);

            float
            distanceFromEye(const TextureResourceInfo&  resource,
                            SurfacePtr                  surface,
                            const math::vec3&           eyePosition);

            static
            int
            lodToMipLevel(int lod, int textureWidth, int textureHeight);

            static
            int
            mipLevelToLod(int mipLevel, int textureWidth, int textureHeight);
        };
    }
}
