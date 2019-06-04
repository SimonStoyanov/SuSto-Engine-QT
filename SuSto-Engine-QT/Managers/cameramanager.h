#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "3rdParty/MathGeoLib/MathGeoLib.h"

class QKeyEvent;

class Camera3D
{
public:
    Camera3D();

    void SetPosition(const float3& pos);
    const float3 GetPosition();

    void SetZDir(const float3& front);
    void SetYDir(const float3& front);
    float3 GetZDir();
    float3 GetYDir();

    void GetCorners(float3* corners);

    void SetNearPlaneDistance(const float& set);
    void SetFarPlaneDistance(const float& set);
    void SetFOV(const float& set);
    void SetAspectRatio(const float& set);
    const float GetNearPlaneDistance() const;
    const float GetFarPlaneDistance() const;
    const float GetVerticalFOV() const;
    const float GetHorizontalFOV() const;
    const float4x4 GetViewMatrix() const;
    const float4x4 GetProjectionMatrix() const;
    const float4x4 GetOpenGLViewMatrix() const;
    const float4x4 GetOpenGLProjectionMatrix() const;

    void MoveFront(const float& speed);
    void MoveBack(const float& speed);
    void MoveRight(const float& speed);
    void MoveLeft(const float& speed);
    void MoveUp(const float& speed);
    void MoveDown(const float& speed);

    void Orbit(const float3& rotate_center, const float& motion_x, const float& motion_y);
    void Rotate(const float& motion_x, const float& motion_y);
    void Focus(const float3& focus_center, const float& distance);
    void Focus(const AABB& aabb);

    void Look(const float3& look_pos);

    void GetElementsToDraw();
    bool CheckInsideFrustum(const AABB& box);
    void SetFrustumCulling(bool set);
    bool GetFrustumCulling();

    Frustum GetFrustum();

    void keyPressEvent(QKeyEvent * event);

private:
    Frustum  frustum;
    float       aspect_ratio = 0.0f;
    float       vertical_fov = 0.0f;

    bool        frustum_culling = true;
};

class CameraManager
{
        friend class AppManager;

public:
    static CameraManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new CameraManager();

            instance->Start();
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            instance->CleanUp();

            delete instance;

            instance = nullptr;
        }
    }

    CameraManager();
    ~CameraManager();

    void Start();
    void Update();
    void CleanUp();

    Camera3D* CreateCamera();
    void DestroyCamera(Camera3D* cam);
    void DestroyAllCameras();
    std::vector<Camera3D*> GetCameras();

    Camera3D* GetEditorCamera() const;

    void SetMouseSensitivity(const float& set);
    void SetWheelSpeed(const float& set);
    void SetCameraSpeed(const float& set);

    const float GetMouseSensitivity() const;
    const float GetWheelSpeed() const;
    const float GetCameraSpeed() const;

    const float* GetViewMatrix() const;

private:
    const bool IsMouseInsideWindow() const;

private:
    Camera3D* editor_camera = nullptr;

    std::vector<Camera3D*> cameras;

    // Camera Movement
    bool  mouse_movement = false;
    float camera_speed = 0.0f;
    float wheel_speed = 0.0f;
    float mouse_sensitivity = 0.0f;

    static CameraManager* instance;
};

#endif // CAMERAMANAGER_H