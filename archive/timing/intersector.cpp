#include <intersector.hpp>

bool Intersector::rectIntersectsRect(AARect& rect_0, AARect& rect_1){
    return (fmaxf(rect_0.getRight(), rect_1.getRight()) - fmin(rect_0.getLeft(), rect_1.getLeft())) <= (rect_0.getWidth() + rect_1.getWidth()) &&
        (fmaxf(rect_0.getBottom(), rect_1.getBottom()) - fmin(rect_0.getTop(), rect_1.getTop())) <= (rect_0.getHeight() + rect_1.getHeight());

}

bool Intersector::circleIntersectsRect(Circle& circle, AARect& rect){
    Polygon rect_polygon = Polygon().create(rect);
    return Intersector::circleIntersectsPolygon(circle, rect_polygon); 
}

// This should work as long as the shappe has a toRect function
template <typename ShapeA, typename ShapeB>
bool Intersector::asRectIntersectsAsRect(ShapeA& a, ShapeB& b){
    AARect rect_a = a.toRect();
    AARect rect_b = b.toRect();
    return Intersector::rectIntersectsRect(rect_a, rect_b);
}

// This Should Work, but needs testing
bool Intersector::circleIntersectsPolygon(Circle& circle, Polygon& polygon){
    if(!Intersector::asRectIntersectsAsRect<Circle, Polygon>(circle, polygon)){
        return false;
    }

    std::vector<Edge> polygon_edges = polygon.getEdges();
    for(int i = 0; i < polygon_edges.size(); i++){
        glm::vec2 point = ExtraVectorMath::lineClamp(
            polygon_edges.at(i).p0, 
            polygon_edges.at(i).p1,
            circle.position + 
                polygon_edges.at(i).getNormal() * 
                ExtraVectorMath::projectionT(circle.position, polygon_edges.at(i).p0, polygon_edges.at(i).getNormal())
        ); 
        if(circle.containsPoint(point)){
            return true;
        }
    }
    return false;
}



bool Intersector::polygonIntersectsPolygonEdgeTest(Polygon& polygon_0, Polygon& polygon_1){

    std::vector<Edge> polygon_0_edges = polygon_0.getEdges();
    std::vector<glm::vec2>& polygon_0_verticies= polygon_0.getVerticies();
    std::vector<glm::vec2>& polygon_1_verticies= polygon_1.getVerticies();
    bool intersecting = true;
    for(int i = 0; i < polygon_0_edges.size(); i++){
        glm::vec2 vector = polygon_0_edges.at(i).asVector();
        glm::vec2 normal = glm::normalize(polygon_0_edges.at(i).getNormal());   

        float min_polygon_0 = ExtraVectorMath::projectionT(
            ExtraVectorMath::projectionPoint(ExtraVectorMath::minPoint(polygon_0_verticies, vector), glm::vec2(0.0f), normal), 
            glm::vec2(0.0f),
            -vector
        ),
        max_polygon_0 = ExtraVectorMath::projectionT(
            ExtraVectorMath::projectionPoint(ExtraVectorMath::maxPoint(polygon_0_verticies, vector), glm::vec2(0.0f), normal),
            glm::vec2(0.0f),
            -vector
        ),
        min_polygon_1 = ExtraVectorMath::projectionT(
            ExtraVectorMath::projectionPoint(ExtraVectorMath::minPoint(polygon_1_verticies, vector), glm::vec2(0.0f), normal), 
            glm::vec2(0.0f),
            -vector
        ),
        max_polygon_1 = ExtraVectorMath::projectionT( 
            ExtraVectorMath::projectionPoint(ExtraVectorMath::maxPoint(polygon_1_verticies, vector), glm::vec2(0.0f), normal),
            glm::vec2(0.0f),
            -vector
        );
        float polygon_0_w = max_polygon_0 - min_polygon_0;
        float polygon_1_w = max_polygon_1 - min_polygon_1;
        float max_max = fmaxf(max_polygon_0, max_polygon_1);
        float min_min = fminf(min_polygon_0, min_polygon_1);
        float intersected_width = (max_max - min_min);
        float total_width = (polygon_0_w + polygon_1_w);
        intersecting = intersecting && ( intersected_width <= total_width);
    }
    return intersecting;

}

bool Intersector::polygonIntersectsPolygon(Polygon& polygon_0, Polygon& polygon_1){

    return Intersector::polygonIntersectsPolygonEdgeTest(polygon_0, polygon_1) && 
    Intersector::polygonIntersectsPolygonEdgeTest(polygon_1, polygon_0);
    
}

bool Intersector::polygonIntersectsRect(Polygon& polygon, AARect& rect){
    Polygon rect_as_polygon;
    rect_as_polygon.create(rect);
    return Intersector::polygonIntersectsPolygon(polygon, rect_as_polygon);
}

bool Intersector::capsuleIntersectsRect(Capsule& capsule, AARect& rect){
    Circle circle_1 = capsule.getStartCircle(); 
    Circle circle_2 = capsule.getEndCircle();
    Polygon polygon = capsule.getMidSection();
    
    return Intersector::circleIntersectsRect(circle_2, rect) ||
        Intersector::polygonIntersectsRect(polygon, rect) || 
        Intersector::circleIntersectsRect(circle_1, rect);
}
