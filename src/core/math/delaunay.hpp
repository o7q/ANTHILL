#pragma once

#include "core/math/circle.hpp"
#include "core/math/edge.hpp"
#include "core/math/triangle.hpp"
#include "core/math/vec.hpp"
#include <vector>

inline std::vector<Triangle2i> generateDelaunayTriangle(const std::vector<Vec2i> &points)
{
    std::vector<Triangle2i> triangulation;

    Triangle2i superTri;
    superTri.verts[0] = {10, 10};
    superTri.verts[1] = {240, 10};
    superTri.verts[2] = {120, 200};

    triangulation.push_back(superTri);

    for (Vec2i p : points)
    {
        std::vector<Triangle2i> badTris;

        for (Triangle2i tri : triangulation)
        {
            Circle2f circ = tri.generateCircumcircle();
            if (circ.pointInside(p.toFloat()))
            {
                badTris.push_back(tri);
            }
        }

        std::vector<Edge2i> poly;

        for (size_t i = 0; i < badTris.size(); ++i)
        {
            for (Edge2i edge1 : badTris[i].generateEdges())
            {
                bool shared = false;

                for (size_t j = 0; j < badTris.size(); ++j)
                {
                    if (i == j)
                    {
                        continue;
                    }

                    for (Edge2i edge2 : badTris[j].generateEdges())
                    {
                        if (edge1 == edge2)
                        {
                            shared = true;
                            break;
                        }
                    }

                    if (shared)
                    {
                        break;
                    }
                }

                if (!shared)
                {
                    poly.push_back(edge1);
                }
            }
        }

        for (Triangle2i badTri : badTris)
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

        for (Edge2i edge : poly)
        {
            Triangle2i tri;
            tri.verts[0] = edge.a;
            tri.verts[1] = edge.b;
            tri.verts[2] = p;
            triangulation.push_back(tri);
        }
    }

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
