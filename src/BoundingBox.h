#pragma once

#include "types.h"
#include <limits>
#include "ray.h"
struct Ray;


namespace {
	inline Vec3f Min3f(const Vec3f a, const Vec3f b)
	{
		return Vec3f(MIN(a.val[0], b.val[0]), MIN(a.val[1], b.val[1]), MIN(a.val[2], b.val[2]));
	}

	inline Vec3f Max3f(const Vec3f a, const Vec3f b)
	{
		return Vec3f(MAX(a.val[0], b.val[0]), MAX(a.val[1], b.val[1]), MAX(a.val[2], b.val[2]));
	}
}

/**
 * @brief Bounding Box class
 */
class CBoundingBox
{
public:
	CBoundingBox(void) = default;
	~CBoundingBox(void)= default;

	/**
	 * @brief Resets the bounding box
	 * @details This function resets the member variables \b m_min and \b m_max
	 */
	void clear(void)
	{
		// --- PUT YOUR CODE HERE ---
		float infinity = std::numeric_limits<float>::infinity();

		m_min[0] = infinity;
		m_min[1] = infinity;
		m_min[2] = infinity;

		m_max[0] = -1 * infinity;
		m_max[1] = -1 * infinity;
		m_max[2] = -1 * infinity;
	}

	/**
	 * @brief Extends the bounding box to contain point \b a
	 * @param a A point
	 */
	void extend(Vec3f a)
	{
		// --- PUT YOUR CODE HERE ---
		m_min = Min3f(m_min, a);
		m_max = Max3f(m_max, a);
	}

	/**
	 * @brief Extends the bounding box to contain bounding box \b box
	 * @param box The second bounding box
	 */
	void extend(const CBoundingBox& box)
	{
		// --- PUT YOUR CODE HERE ---
		this->extend(box.m_min);
		this->extend(box.m_max);
	}

	/**
	 * @brief Checks if the current bounding box overlaps with the argument bounding box \b box
	 * @param box The secind bounding box to be checked with
	 */
	bool overlaps(const CBoundingBox& box)
	{
		// --- PUT YOUR CODE HERE ---
		bool overlapX = m_min[0] <= box.m_max[0] && box.m_min[0] <= m_max[0];
		bool overlapY = m_min[1] <= box.m_max[1] && box.m_min[1] <= m_max[1];
		bool overlapZ = m_min[2] <= box.m_max[2] && box.m_min[2] <= m_max[2];
		return overlapX && overlapY && overlapZ;
	}

	/**
	 * @brief Clips the ray with the bounding box
	 * @param[in] ray The ray
	 * @param[in,out] t0 The distance from ray origin at which the ray enters the bounding box
	 * @param[in,out] t1 The distance from ray origin at which the ray leaves the bounding box
	 */
	void clip(const Ray& ray, float& t0, float& t1)
	{
		// --- PUT YOUR CODE HERE ---
		Vec3f t_0;
		Vec3f t_1;

		float infinity = std::numeric_limits<float>::infinity();

		float t_negative = -1 * infinity;
		float t_positive = infinity;

		int counter = 0;

		while(counter != 3){
			if(ray.dir[counter] == 0){
				if((this->m_min[counter] > ray.org[counter]) || (this->m_max[counter] < ray.org[counter])){
					t0 = infinity;
					t1 = infinity;
					return;
				}
			}
			else{
				t_0[counter] = (this->m_min[counter] - ray.org[counter]) / ray.dir[counter];
				t_1[counter] = (this->m_max[counter] - ray.org[counter]) / ray.dir[counter];

				if(t_negative < t_0[counter]){
					t_negative = t_0[counter];
				}

				if(t_positive > t_1[counter]){
					t_positive = t_1[counter];
				}

				if(t_1[counter] < t_0[counter]){
					Vec3f place_holder;
					place_holder = t_1;
					t_1 = t_0;
					t_0 = place_holder;
				}

				if((t_positive < t_negative) || (t_positive < 0)){
					t0 = infinity;
					t1 = infinity;
					return;
				}

			}
			counter++;
		}
		t0 = t_negative;
		t1 = t_positive;
	}


public:
	Vec3f m_min;	///< The minimal point defying the size of the bounding box
	Vec3f m_max;	///< The maximal point defying the size of the bounding box
};
