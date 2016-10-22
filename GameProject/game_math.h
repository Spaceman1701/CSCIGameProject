#pragma once

float clampf(float v, float min, float max);

bool lineIntersect(const Vector2& l1s, const Vector2& l1e, const Vector2& l2s, const Vector2& l2e, Vector2& result);

float signedTriArea(const Vector2& a, const Vector2& b, const Vector2& c); //from "Real Time Collision Detection"
