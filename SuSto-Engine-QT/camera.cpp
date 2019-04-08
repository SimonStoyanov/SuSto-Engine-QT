#include "camera.h"
#include <QtMath>

Camera::Camera()
{
}

QVector4D Camera::getLeftRightBottomTop()
{
    const float aspectRatio = float(viewportWidth) / viewportHeight;
    const float alpha = qDegreesToRadians(fovy * 0.5);
    const float top = znear * qTan(alpha);
    const float bottom = -top;
    const float right = top * aspectRatio;
    const float left = -right;
    QVector4D params(left, right, bottom, top);
    return params;
}

QVector3D Camera::screenPointToWorldRay(int x, int y)
{
    return QVector3D();
}

QVector3D Camera::screenDisplacementToWorldVector(int x0, int y0, int x1, int y1, const QVector3D &worldPoint)
{
    return QVector3D();
}

QVector3D Camera::worldToScreenPoint(const QVector3D &p)
{
    return QVector3D();
}

void Camera::prepareMatrices()
{
    worldMatrix.setToIdentity();
}
