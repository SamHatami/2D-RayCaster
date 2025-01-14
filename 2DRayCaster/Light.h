#pragma once
#include <iosfwd>
#include <memory>
#include <vector>
#include <vector>
#include "Ray.h"
#include "Geometry.h"
#include "Wall.h"

class Light
{
public:
	enum class LightType
	{
		Point,
		Spot,
		Directional
	};

	enum class LightBehaviour
	{
		Static,
		Dynamic
	};

	enum class Resolution
	{
		Low = 64,
		Medium = 128,
		High = 256
	};

	static Resolution globalResolution; // Could control all lights' ray count
	static constexpr float MAX_RAY_LENGTH = 200;

protected:
	float intensity;
	uint32_t color;
	LightType lightType;
	Point position;
	//LightBehaviour lightBehaviour; TODO
	std::vector<Ray> rays;
	float rayLength; // Each pointLight controls its own ray length

	Light(LightType type, float intensity = 100.0f, uint32_t color = 0xFFFFFF00, float rayLength = 100.0f, Point position = {0,0})
		: intensity(intensity)
		, color(color)
		, lightType(type)
		, position(position)
		, rayLength(rayLength)
	{
		rays.resize(static_cast<size_t>(globalResolution));
	}

public:
	virtual ~Light() = default;

	float getIntensity() const;

	virtual void castRays(const std::vector<Point> points = {});

	uint32_t getColor() const;
	void setColor(uint32_t newColor);

	LightType getType() const;

	void decreaseIntensity();
	void increaseIntensity();

	Point& getPosition();
	void setPosition(const Point& pos);

	std::vector<Ray>& getRays();

	static int getCurrentResolution();

	friend class LightingSystem;
};
