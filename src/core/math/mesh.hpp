#pragma once

#include "core/math/geometry/triangle.hpp"
#include <limits>

namespace Math
{
namespace Mesh
{
// https://www.gorillasun.de/blog/bowyer-watson-algorithm-for-delaunay-triangulation/#an-intuitive-explanation-of-the-algorithm
inline std::vector<Triangle_i> generateTriangulation(const std::vector<Vec2i> &points)
{
    std::vector<Triangle_i> triangulation;

    Triangle_i superTri;

    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();

    for (Vec2i p : points)
    {
        minX = std::min(minX, p.x);
        minY = std::min(minY, p.y);
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
    }
    int dx = maxX - minX;
    int dy = maxY - minY;

    superTri.verts[0] = {minX - dx, minY - dy * 3};
    superTri.verts[1] = {minX - dx, maxY + dy};
    superTri.verts[2] = {maxX + dx * 3, maxY + dy};

    triangulation.push_back(superTri);

    for (Vec2i p : points)
    {
        std::vector<Triangle_i> badTris;

        for (Triangle_i tri : triangulation)
        {
            Circle_i c = tri.generateCircumcircle();
            if (c.pointInside(p))
            {
                badTris.push_back(tri);
            }
        }

        std::vector<Segment_i> poly;
        for (size_t i = 0; i < badTris.size(); ++i)
        {
            for (Segment_i edge1 : badTris[i].generateSegments())
            {
                bool sharedWithBad = false;

                for (size_t j = 0; j < badTris.size(); ++j)
                {
                    if (i == j)
                    {
                        continue;
                    }

                    for (Segment_i edge2 : badTris[j].generateSegments())
                    {
                        if (edge1 == edge2)
                        {
                            sharedWithBad = true;
                            break;
                        }
                    }

                    if (sharedWithBad)
                    {
                        break;
                    }
                }

                if (!sharedWithBad)
                {
                    poly.push_back(edge1);
                }
            }
        }

        // remove bad tris
        for (Triangle_i badTri : badTris)
        {
            for (auto it = triangulation.begin(); it != triangulation.end();)
            {
                if (*it == badTri)
                {
                    it = triangulation.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        // create new tris
        for (Segment_i edge : poly)
        {
            Triangle_i tri;
            tri.verts[0] = edge.a;
            tri.verts[1] = edge.b;
            tri.verts[2] = p;
            triangulation.push_back(tri);
        }
    }

    // remove tris related to the super-tri
    for (auto it = triangulation.begin(); it != triangulation.end();)
    {
        bool containsVert = false;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (it->verts[i] == superTri.verts[j])
                {
                    containsVert = true;
                    break;
                }
            }

            if (containsVert)
            {
                break;
            }
        }

        if (containsVert)
        {
            it = triangulation.erase(it);
        }
        else
        {
            it++;
        }
    }

    return triangulation;
}
} // namespace Mesh
} // namespace Math
