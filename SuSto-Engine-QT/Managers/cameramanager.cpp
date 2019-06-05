#include "cameramanager.h"
#include "Managers/appmanager.h"
#include "globals.h"
#include "Entity/entity.h"
#include <QTime>
#include <QKeyEvent>
#include "Managers/inputmanager.h"

//----------------------//
//----CAMERA MANAGER----//
//----------------------//

CameraManager* CameraManager::instance = nullptr;

CameraManager::CameraManager()
{
    editor_camera = CreateCamera();
}

CameraManager::~CameraManager()
{}

void CameraManager::Start()
{
}

void CameraManager::CleanUp()
{
    bool ret = true;

    SPOOKYLOG("Cleaning cameras");

    DestroyAllCameras();
}

Camera3D * CameraManager::CreateCamera()
{
    Camera3D* ret = nullptr;

    ret = new Camera3D();
    cameras.push_back(ret);

    return ret;
}

void CameraManager::DestroyCamera(Camera3D * cam)
{
    for (std::vector<Camera3D*>::iterator it = cameras.begin(); it != cameras.end();)
    {
        if (cam == (*it))
        {
            delete(*it);
            cameras.erase(it);
            break;
        }
        else
            ++it;
    }
}

void CameraManager::DestroyAllCameras()
{
    for (std::vector<Camera3D*>::iterator it = cameras.begin(); it != cameras.end();)
    {
        delete(*it);
        it = cameras.erase(it);
    }
}

std::vector<Camera3D*> CameraManager::GetCameras()
{
    return cameras;
}

Camera3D * CameraManager::GetEditorCamera() const
{
    return editor_camera;
}

void CameraManager::SetMouseSensitivity(const float& set)
{
    mouse_sensitivity = set;
}

void CameraManager::SetWheelSpeed(const float& set)
{
    wheel_speed = set;
}

void CameraManager::SetCameraSpeed(const float& set)
{
    camera_speed = set;
}

const float CameraManager::GetMouseSensitivity() const
{
    return mouse_sensitivity;
}

const float CameraManager::GetWheelSpeed() const
{
    return wheel_speed;
}

const float CameraManager::GetCameraSpeed() const
{
    return camera_speed;
}

const float * CameraManager::GetViewMatrix() const
{
    return editor_camera->GetOpenGLViewMatrix().ptr();
}

// -----------------------------------------------------------------
void CameraManager::Update()
{
    bool ret = true;

    float cam_speed = 50 * AppManager::Instance()->GetDT();
    float whe_speed = 50 * AppManager::Instance()->GetDT();
    float mou_speed = 3 * AppManager::Instance()->GetDT();

    if(InputManager::Instance()->KeyRepeat(Qt::Key::Key_W))
    {
        editor_camera->MoveFront(cam_speed);
    }

    if(InputManager::Instance()->KeyRepeat(Qt::Key::Key_A))
    {
        editor_camera->MoveLeft(cam_speed);
    }

    if(InputManager::Instance()->KeyRepeat(Qt::Key::Key_D))
    {
        editor_camera->MoveRight(cam_speed);
    }

    if(InputManager::Instance()->KeyRepeat(Qt::Key::Key_S))
    {
        editor_camera->MoveBack(cam_speed);
    }

    if(InputManager::Instance()->KeyRepeat(Qt::Key::Key_Z))
    {
        editor_camera->MoveUp(cam_speed);
    }

    if(InputManager::Instance()->KeyRepeat(Qt::Key::Key_X))
    {
        editor_camera->MoveDown(cam_speed);
    }

    if(InputManager::Instance()->MouseButtonRepeat(Qt::MouseButton::RightButton))
    {
        float2 movement = InputManager::Instance()->MouseMovement();

        editor_camera->Rotate(-movement.x * mou_speed, -movement.y * mou_speed);
    }

    /*SPOOKYLOG(std::to_string(editor_camera->GetFrustum().Pos().x) + " " +
              std::to_string(editor_camera->GetFrustum().Pos().y) + " " +
              std::to_string(editor_camera->GetFrustum().Pos().z));

    SPOOKYLOG(std::to_string(editor_camera->GetFrustum().ViewMatrix()[0][0]) + " " +
              std::to_string(editor_camera->GetFrustum().ViewMatrix()[1][0]) + " " +
              std::to_string(editor_camera->GetFrustum().ViewMatrix()[2][0]));*/

    /*if (App->input->GetKeyRepeat(SDL_SCANCODE_LSHIFT))
        cam_speed = camera_speed/2 * AppManager::Instance()->GetDT();

    if (IsMouseInsideWindow())
    {
        mouse_movement = true;
    }

    // Mouse motion ----------------
    if (mouse_movement)
    {
        if (App->input->GetMouseWheel() == 1)
        {
            editor_camera->MoveFront(whe_speed);
        }
        else if (App->input->GetMouseWheel() == -1)
        {
            editor_camera->MoveBack(whe_speed);
        }

        if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
        {
            App->window->GetCursor()->Hand();

            if (App->input->GetKeyRepeat(SDL_SCANCODE_Z))
                editor_camera->MoveUp(cam_speed);

            if (App->input->GetKeyRepeat(SDL_SCANCODE_X))
                editor_camera->MoveDown(cam_speed);

            if (App->input->GetKeyRepeat(SDL_SCANCODE_W))
                editor_camera->MoveFront(cam_speed);

            if (App->input->GetKeyRepeat(SDL_SCANCODE_S))
                editor_camera->MoveBack(cam_speed);

            if (App->input->GetKeyRepeat(SDL_SCANCODE_A))
                editor_camera->MoveLeft(cam_speed);

            if (App->input->GetKeyRepeat(SDL_SCANCODE_D))
                editor_camera->MoveRight(cam_speed);

            editor_camera->Rotate(-App->input->GetMouseXMotion()*mou_speed, -App->input->GetMouseYMotion()*mou_speed);

            App->gameobj->SetCanMove(false);

        }
        else if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
        {
            if (App->input->GetKeyRepeat(SDL_SCANCODE_LALT) || App->input->GetKeyRepeat(SDL_SCANCODE_RALT))
            {
                if (App->input->GetKeyRepeat(SDL_SCANCODE_W))
                    editor_camera->MoveFront(cam_speed);

                if (App->input->GetKeyRepeat(SDL_SCANCODE_S))
                    editor_camera->MoveBack(cam_speed);

                editor_camera->Orbit(float3(0, 0, 0), -App->input->GetMouseXMotion()*mou_speed, -App->input->GetMouseYMotion()*mou_speed);
                editor_camera->Look(float3(0, 0, 0));

                App->window->GetCursor()->SizeAll();

                App->gameobj->SetCanMove(false);
            }
        }
        else
        {
            mouse_movement = false;
            App->gameobj->SetCanMove(true);
        }
    }

    if (App->input->GetKeyDown("f"))
    {
        editor_camera->Focus(float3(0, 0, 0), 10);
    }
*/
}

const bool CameraManager::IsMouseInsideWindow() const
{
   return true;
}

//----------------//
//----CAMERA3D----//
//----------------//

Camera3D::Camera3D()
{
    frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);

    frustum.SetPos(float3(0, 1, -1));
    frustum.SetFront(float3::unitZ);
    frustum.SetUp(float3::unitY);
    aspect_ratio = 0;

    SetNearPlaneDistance(0.1f);
    SetFarPlaneDistance(10000.0f);
    SetAspectRatio(1.3f);
    SetFOV(60);
}

void Camera3D::SetPosition(const float3 & pos)
{
    frustum.SetPos(pos);
}

const float3 Camera3D::GetPosition()
{
    return frustum.Pos();
}

void Camera3D::SetZDir(const float3 & front)
{
    frustum.SetFront(front.Normalized());
}

void Camera3D::SetYDir(const float3 & front)
{
    frustum.SetUp(front.Normalized());
}

float3 Camera3D::GetZDir()
{
    return frustum.Front();
}

float3 Camera3D::GetYDir()
{
    return frustum.Up();
}

void Camera3D::GetCorners(float3* corners)
{
    frustum.GetCornerPoints(corners);
}

void Camera3D::SetNearPlaneDistance(const float & set)
{
    frustum.SetViewPlaneDistances(set, frustum.FarPlaneDistance());
}

void Camera3D::SetFarPlaneDistance(const float & set)
{
    frustum.SetViewPlaneDistances(frustum.NearPlaneDistance(), set);
}

void Camera3D::SetFOV(const float & set)
{
    if (set > 0)
    {
        vertical_fov = DEGTORAD(set);
        frustum.SetVerticalFovAndAspectRatio(vertical_fov, aspect_ratio);
    }
}

void Camera3D::SetAspectRatio(const float & set)
{
    if (set > 0)
    {
        aspect_ratio = set;
        frustum.SetVerticalFovAndAspectRatio(vertical_fov, set);
    }
}

const float Camera3D::GetNearPlaneDistance() const
{
    return frustum.NearPlaneDistance();
}

const float Camera3D::GetFarPlaneDistance() const
{
    return frustum.FarPlaneDistance();
}

const float Camera3D::GetVerticalFOV() const
{
    return RADTODEG(frustum.VerticalFov());
}

const float Camera3D::GetHorizontalFOV() const
{
    return RADTODEG(frustum.HorizontalFov());
}

const float4x4 Camera3D::GetViewMatrix() const
{
    return frustum.ViewMatrix();
}

const float4x4 Camera3D::GetProjectionMatrix() const
{
    return frustum.ProjectionMatrix();
}

const float4x4 Camera3D::GetOpenGLViewMatrix() const
{
    float4x4 view = frustum.ViewMatrix();
    return view.Transposed();
}

const float4x4 Camera3D::GetOpenGLProjectionMatrix() const
{
    return frustum.ProjectionMatrix().Transposed();
}

void Camera3D::MoveFront(const float & speed)
{
    if (speed <= 0)
        return;

    float3 movement = float3::zero;
    movement += frustum.Front() * speed;

    float3 new_pos = frustum.Pos() + movement;

    frustum.SetPos(new_pos);
}

void Camera3D::MoveBack(const float & speed)
{
    if (speed <= 0)
        return;

    float3 movement = float3::zero;
    movement -= frustum.Front() * speed;

    float3 new_pos = frustum.Pos() + movement;

    frustum.SetPos(new_pos);
}

void Camera3D::MoveRight(const float & speed)
{
    if (speed <= 0)
        return;

    float3 movement = float3::zero;
    movement += frustum.WorldRight() * speed;

    float3 new_pos = frustum.Pos() + movement;

    frustum.SetPos(new_pos);
}

void Camera3D::MoveLeft(const float & speed)
{
    if (speed <= 0)
        return;

    float3 movement = float3::zero;
    movement -= frustum.WorldRight() * speed;

    float3 new_pos = frustum.Pos() + movement;

    frustum.SetPos(new_pos);
}

void Camera3D::MoveUp(const float & speed)
{
    if (speed <= 0)
        return;

    float3 movement = float3::zero;
    movement += float3::unitY * speed;

    float3 new_pos = frustum.Pos() + movement;

    frustum.SetPos(new_pos);
}

void Camera3D::MoveDown(const float & speed)
{
    if (speed <= 0)
        return;

    float3 movement = float3::zero;
    movement -= float3::unitY * speed;

    float3 new_pos = frustum.Pos() + movement;

    frustum.SetPos(new_pos);
}

void Camera3D::Orbit(const float3 & rotate_center, const float & motion_x, const float & motion_y)
{
    float3 distance = frustum.Pos() - rotate_center;

    Quat X(frustum.WorldRight(), motion_y);
    Quat Y(frustum.Up(), motion_x);

    distance = X.Transform(distance);
    distance = Y.Transform(distance);

    frustum.SetPos(distance + rotate_center);
}

void Camera3D::Rotate(const float & motion_x, const float & motion_y)
{    
    if(motion_x != 0)
    {
        Quat rotation_x = Quat::RotateY(motion_x);
        frustum.SetFront(rotation_x.Mul(frustum.Front()).Normalized());
        frustum.SetUp(rotation_x.Mul(frustum.Up()).Normalized());
    }

    if(motion_y != 0)
    {
        Quat rotation_y = Quat::RotateAxisAngle(frustum.WorldRight(), motion_y);
        frustum.SetFront(rotation_y.Mul(frustum.Front()).Normalized());
        frustum.SetUp(rotation_y.Mul(frustum.Up()).Normalized());
    }
}

void Camera3D::Look(const float3 & look_pos)
{
    float3 dir = look_pos - frustum.Pos();

    float3x3 direction_matrix = float3x3::LookAt(frustum.Front(), dir.Normalized(), frustum.Up(), float3::unitY);

    frustum.SetFront(direction_matrix.MulDir(frustum.Front()).Normalized());
    frustum.SetUp(direction_matrix.MulDir(frustum.Up()).Normalized());
}

bool Camera3D::CheckInsideFrustum(const AABB & box)
{
    bool ret = true;

    // Get aabb corners
    float3 corners[8];
    box.GetCornerPoints(corners);

    // Test all corners for each plane
    for (int p = 0; p < 6; ++p)
    {
        uint corners_in = 8;

        for (int c = 0; c < 8; ++c)
        {
            if (frustum.GetPlane(p).IsOnPositiveSide(corners[c]))
            {
                corners_in--;
            }
        }

        if (corners_in == 0)
        {
            ret = false;
            break;
        }
    }

    return ret;
}

void Camera3D::SetFrustumCulling(bool set)
{
    frustum_culling = set;
}

bool Camera3D::GetFrustumCulling()
{
    return frustum_culling;
}

Frustum Camera3D::GetFrustum()
{
    return frustum;
}

void Camera3D::Focus(const float3 & focus_center, const float & distance)
{
    float3 dir = frustum.Pos() - focus_center;
    frustum.SetPos(dir.Normalized() * distance);

    Look(focus_center);
}

void Camera3D::Focus(const AABB & aabb)
{
    Focus(aabb.CenterPoint(), aabb.Size().Length());
}
