// 判断 3D 空间中的一条光线 PQ 与三角形 ABC 是否相交
#include <cmath>
#include <limits>
#include <functional>
#include <iostream>

using namespace std;

// precomputation

// 这个点结构也可以代表向量
struct Point
{
    double x, y, z;
};

Point operator/(const Point& p, const double& scalar)
{
    return Point{p.x / scalar, p.y / scalar, p.z / scalar};
}

// 计算两个向量的叉积
Point crossProduct(const Point& A, const Point& B)
{
    return Point{
        A.y * B.z - A.z * B.y,
        A.z * B.x - A.x * B.z,
        A.x * B.y - A.y * B.x
    };
}

// 计算两个向量的点积
const double dotProduct(const Point& A, const Point& B)
{
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

const Point A = {0, 0, 0};
const Point B = {1, 0, 0};
const Point C = {0, 1, 0};
const Point P = {0, 0, 1};
const Point d = {0, 0, 1}; // 光线方向为 (0, 0, 1)

// 计算三角形所在平面的法向量，AB X AC
const Point n = crossProduct(Point{B.x-A.x, B.y-A.y, B.z-A.z}, Point{C.x-A.x, C.y-A.y, C.z-A.z});
// 计算 AB 的垂直向量，即 n X AB，并且归一化
// 注意，这里的除号需要重载
const Point& ABp = crossProduct(n, Point{B.x-A.x, B.y-A.y, B.z-A.z});
const Point& ABpn = ABp / dotProduct(Point{C.x-A.x, C.y-A.y, C.z-A.z}, ABp);

// 对于 AC 同理
const Point& ACp = crossProduct(n, Point{C.x-A.x, C.y-A.y, C.z-A.z});
const Point& ACpn = ACp / dotProduct(Point{B.x-A.x, B.y-A.y, B.z-A.z}, ACp);

// 接下来是计算交点 Q 的 t 值以及重心坐标 
// 首先，根据已知的 t 表达式，我们准备相关的数据
const double nd = dotProduct(n, d);

int main()
{
    function<bool()> intersect = [&]() {
        if(fabs(nd) < 1e-9)
        {
            // 此时可以认为光线和平面几乎是平行的，没有交点，我们直接返回
            return false;
        }        
        // 计算 t
        const double t = dotProduct(n, Point{A.x-P.x, A.y-P.y, A.z-P.z}) / nd;
        if(t < 0)
        {
            // 此时交点在光线的反方向上，我们也认为没有交点
            return false;
        }
        // 否则，可以计算交点 Q，根据 t 值即可求出
        const Point Q = Point{P.x + t * d.x, P.y + t * d.y, P.z + t * d.z};
        // 计算重心坐标
        const double gamma = dotProduct(Point{Q.x-C.x, Q.y-C.y, Q.z-C.z}, ACpn);
        const double beta = dotProduct(Point{Q.x-B.x, Q.y-B.y, Q.z-B.z}, ABpn);
        const double alpha = 1 - beta - gamma; 
        // 判断是否在三角形内
        // 只要至少有一个重心坐标小于 0 或大于 1，就说明 Q 在三角形外
        if(alpha < -1e-9 || alpha > 1 + 1e-9 ||
           beta < -1e-9 || beta > 1 + 1e-9 ||
           gamma < -1e-9 || gamma > 1 + 1e-9)
        {
            return false;
        }
        // 否则，说明在三角形内
        return true;
    };
    if(intersect())
    {
        cout << "The ray intersects the triangle." << endl;
    }
    else
    {
        cout << "The ray does not intersect the triangle." << endl;
    }
}