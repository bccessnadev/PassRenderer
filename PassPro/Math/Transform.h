#pragma once
#include "VectorLibrary.h"

/**
 * The Transform2D class represents a 2D transformation.
 *
 * This class provides functionality to handle 2D transformations including position,
 * rotation, and scale. It offers methods to get and set these properties, as well as
 * to apply local and global translations and rotations.
 */
class Transform2D
{
public:
	Transform2D() {}

	 /** 
     * @Constructs a Transform2D with the specified position, rotation, and scale.
     * 
     * @param Position The initial position.
     * @param RotationInRads The initial rotation in radians.
     * @param Scale The initial scale.
     */
	Transform2D(const Vector2& Position, const float RotationInRads, const Vector2& Scale);

	/**
	 * Gets the transformation matrix.
	 *
	 * @return A reference to the transformation matrix.
	 */
	const Matrix2D& GetMatrix() const { return Matrix; }
	
	/**
	 * Sets the position.
	 *
	 * @param Position The new position.
	 */
	void SetPosition(const Vector2& Position);

	/**
	 * Gets the position.
	 *
	 * @return The current position.
	 */
	Vector2 GetPosition() const;

	/**
	 * Sets the rotation.
	 *
	 * @param RotationInRads The new rotation in radians.
	 */
	void SetRotation(const float RotationInRads);

	/**
	 * Gets the scale.
	 *
	 * @return The current scale.
	 */
	Vector2 GetScale() const;

	/**
	 * Sets the scale.
	 *
	 * @param Scale The new scale.
	 */
	void SetScale(const Vector2& Scale);

	/**
	 * Translates the position locally.
	 *
	 * @param Translation The translation vector.
	 */
	void TranslateLocal(const Vector2& Translation);

	/**
	 * Translates the position globally.
	 *
	 * @param Translation The translation vector.
	 */
	void TranslateGlobal(const Vector2& Translation);

	/**
	 * Rotates the transformation locally.
	 *
	 * @param Rotation The rotation angle in radians.
	 */
	void RotateLocal(const float Rotation);

	/**
	 * Gets the rotation matrix.
	 *
	 * @return The rotation matrix.
	 */
	Matrix2D GetRotationMatrix() const;

	/**
	 * Gets the rotation angle.
	 *
	 * @return The rotation angle in radians.
	 */
	float GetRotationAngle() const;

protected:
	/** The transformation matrix. */
	Matrix2D Matrix;
};