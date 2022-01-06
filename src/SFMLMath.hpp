//
// Created by Denis Wagner on 1/16/19.
//

#ifndef PONG_SFMLMATH_HPP
#define PONG_SFMLMATH_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sf
{
    static const auto PI = acos( -1 );

    /*
     * Vector addition
     */
    template <typename T>
    T operator+( const T& vec1, const T& vec2 )
    {
        const auto newX = vec1.x + vec2.x;
        const auto newY = vec1.y + vec2.y;

        return T( newX, newY );
    }

    /*
     * Vector subtraction
     */
    template <typename T>
    T operator-( const T& vec1, const T& vec2 )
    {
        const auto newX = vec1.x - vec2.x;
        const auto newY = vec1.y - vec2.y;

        return T( newX, newY );
    }

    /*
     * Scalar multiplication
     */
    template <typename T, typename U>
    T operator*( const T& vec, U scalar )
    {
        const auto newX = vec.x * scalar;
        const auto newY = vec.y * scalar;

        return T( newX, newY );
    }

    /*
     * Scalar multiplication
     */
    template <typename U, typename T>
    T operator*( U scalar, const T& vec )
    {
        const auto newX = vec.x * scalar;
        const auto newY = vec.y * scalar;

        return T( newX, newY );
    }

    /*
     * Returns the dot product of two given vectors
     */
    template <typename T>
    double operator*( const T& vec1, const T& vec2 )
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    /*
     * Returns the square of a given value
     */
    template <typename T>
    inline T sqr( T value )
    {
        return value * value;
    }

    /*
     * Converts radians to degrees
     */
    template <typename T>
    inline double radToDeg( T radians )
    {
        return radians * 180.0 / PI;
    }

    /*
     * Converts degrees to radian
     */
    template <typename T>
    inline double degToRad( T degree )
    {
        return degree / 180.0 * PI;
    }

    /*
     * Returns the length of a given vector
     */
    template <typename T>
    inline double getLength( const T& vec )
    {
        return sqrt( sqr( vec.x ) + sqr( vec.y ) );
    }

    /*
     * Returns an inverted vector
     */
    template <typename T>
    inline T getInverted( const T& vec )
    {
        return T( -vec.x, -vec.y );
    }

    /*
     * Inverts a given vector in-place
     */
    template <typename T>
    inline T& invert( T& vec )
    {
        vec.x = -vec.x;
        vec.y = -vec.y;

        return vec;
    }

    /*
     * Returns a normalized vector
     */
    template <typename T>
    inline T getNormalized( const T& vec )
    {
        const double length = getLength( vec );
        const double newX   = vec.x / length;
        const double newY   = vec.y / length;

        return T( newX, newY );
    }

    /*
     * Normalizes a given vector in-place
     */
    template <typename T>
    inline T& normalize( T& vec )
    {
        const double length = getLength( vec );
        vec.x /= length;
        vec.y /= length;

        return vec;
    }

    /*
     * Returns the angle of a given vector from 0 to 360° depending its direction on the unit circle
     */
    template <typename T>
    inline double getRotationAngle( const T& vec )
    {
        const T      normalizedVec = getNormalized( vec );
        const double angleXRad     = acos( normalizedVec.x );
        const double angleYRad     = asin( normalizedVec.y );
        double       angleRad;

        if ( angleYRad < 0 )
            angleRad = degToRad( 360 ) - angleXRad;
        else
            angleRad = angleXRad;

        return radToDeg( angleRad );
    }

    /*
     * Returns the angle in degrees between two given vectors
     */
    template <typename T>
    inline double getAngleBetween( const T& vec1, const T& vec2 )
    {
        const double angle = acos( ( vec1 * vec2 ) / ( getLength( vec1 ) * getLength( vec2 ) ) );

        return radToDeg( angle );
    }

    /*
     * Returns a vector rotated with a given angle in degrees
     */
    template <typename T>
    inline void getRotated( const T& vec, double angle )
    {
        const double angleRad = degToRad( -angle );
        const double newX     = vec.x * cos( angleRad ) - vec.y * sin( angleRad );
        const double newY     = vec.x * sin( angleRad ) + vec.y * cos( angleRad );

        return T( newX, newY );
    }

    /*
     * Rotates a vector in-place with a given angle in degrees
     */
    template <typename T>
    inline T& rotate( T& vec, double angle )
    {
        const double angleRad = degToRad( -angle );
        
        vec.x = vec.x * cos( angleRad ) - vec.y * sin( angleRad );
        vec.y = vec.x * sin( angleRad ) + vec.y * cos( angleRad );

        return vec;
    }
}
#endif //PONG_SFMLMATH_HPP
