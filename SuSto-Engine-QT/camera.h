#ifndef CAMERA_H
#define CAMERA_H

#define DEFAULT_CAMERA_FOVY 10.0f
#define DEFAULT_CAMERA_ZNEAR 10.0f
#define DEFAULT_CAMERA_ZFAR 10.0f
#define DEFAULT_CAMERA_SPEED 10.0f

#include <QVector4D>
#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();

    QVector4D getLeftRightBottomTop();

    QVector3D screenPointToWorldRay(int x, int y);
    QVector3D screenDisplacementToWorldVector(int x0, int y0, int x1, int y1, const QVector3D &worldPoint);
    QVector3D worldToScreenPoint(const QVector3D &p);

    void prepareMatrices();

    // Viewport
    int viewportWidth = 128;
    int viewportHeight = 128;

    // Projection
    float fovy = DEFAULT_CAMERA_FOVY;
    float znear = DEFAULT_CAMERA_ZNEAR;
    float zfar = DEFAULT_CAMERA_ZFAR;

    // World Navigation
    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position;

    // Speed
    float speed = DEFAULT_CAMERA_SPEED;

    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;
};

#endif // CAMERA_H
