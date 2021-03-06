//
// Created by antonpp on 13.01.17.
//

#ifndef AU_CG_SCENECONTROLLLISTENER_H
#define AU_CG_SCENECONTROLLLISTENER_H


// local
#include "AbstractWindowListener.h"
#include "LightingSphereRenderer.h"
#include "PhongObjectRenderer.h"
#include "CameraObject.h"
#include "WindowWrapper.h"
#include "AxisRenderer.h"
#include "ImageRenderer.h"
#include "PhongTextureRenderer.h"

class Scene : public AbstractWindowListener {
public:

    Scene(std::shared_ptr<WindowWrapper> window);

    void onKeyEvent(int key, int scancode, int action, int mods) override;

private:
    std::shared_ptr<CameraObject> camera_ptr;

    std::shared_ptr<WindowWrapper> window;
    std::shared_ptr<PhongObjectRenderer> objectRenderer;
    std::shared_ptr<PhongTextureRenderer> imageRenderer;
    std::shared_ptr<AxisRenderer> axisRenderer;
    std::vector<std::shared_ptr<LightingSphereRenderer>> lightsRenderers;

    void add_light();
    void remove_light();

    void update_renderers() const;

    static const int MAX_LIGHTS = 32;
};


#endif //AU_CG_SCENECONTROLLLISTENER_H
