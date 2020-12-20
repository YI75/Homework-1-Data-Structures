#include "stats.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

namespace main_savitch_2C {

    /*Constructor for statistician class. Sets m_count and m_total to 0.
    Postcondition: the object is initialized and ready to recieve numbers for calculations.
    Does not initialize m_largest and m_tinyest because no numbers have been placed yet.*/
    statistician::statistician() {
        m_count = 0;
        m_total = 0;
    };

    /*Precondition: r must be a double
    * Postcondition: r is the next number in the sequence
    */
    void statistician::next(double r) {
        //Assert m_count and m_total are not negative. 
        assert(m_count >= 0 && m_total >= 0);
        //If the statistician is empty, r becomes the smallest and
        //largest number in the sequence.
        if (m_count == 0) {
            m_largest = r;
            m_tinyest = r;
        }
        //If the statistician is not empty, check if r is the 
        //new smallest or largest number in the sequnce.
        else {
            if (r > m_largest) {
                m_largest = r;
            }
            if (r < m_tinyest) {
                m_tinyest = r;
            }
        }
        //Update the sum and number of numbers of the sequence.
        m_total = m_total + r;
        m_count++;
    }
    /*Postcondition: statistician is cleared, setting 
    * m_count and m_total to 0.
    * Reset is like making the current object into
    * a new one. The last m_tinyest and m_largest are not directly changed, but
    * you cannot access them unless m_count > 0.
    */
    void statistician::reset() {
        m_count = 0;
        m_total = 0;
    }
    /*Postcondition: return m_count, number of numbers in the sequence.
    */
    int statistician::length() const {
        //As a safety measure, check m_count is not negative.
        assert(m_count >= 0);
        return m_count;
    }
    /*Postcondition: return m_total, the current sum of the sequence.
    */
    double statistician::sum() const {
        //As a safety measure, check m_count is not negative.
        assert(m_count >= 0);
        return m_total;
    }
    /*Precondition: m_count must be greater than 0, statistician class
    * not empty.
    Postcondition: return average of the sequence,
    */
    double statistician::mean() const {
        //Check statistician is not empty, cannot divide by zero.
        //average = sum of sequence divided by number of numbers in the sequence.
        assert(m_count > 0);
        return (m_total / double(m_count));
    }
    /*Precondition: the statistician must not be empty, m_count > 0
    * Postcondition: return smallest number in the sequence.
    */
    double statistician::minimum() const {
        assert(m_count > 0);
        return m_tinyest;
    }
    /*Precondition: the statistician must not be empty, m_count > 0
    * Postcondition: return largest number in the sequence.
    */
    double statistician::maximum() const {
        assert(m_count > 0);
        return m_largest;
    }
    /*Postcondition: statistician returned contains all the
    numbers of the sequences of s1 and s2. 
    */
    statistician operator +(const statistician& s1, const statistician& s2) {
        //checks if either s1 or s2 is empty
        //If one of them is empty, return the non-empty statistician. 
        //If both are empty, the sum will be an empty statistician anyway.
        if (s1.length() == 0) {
            return s2;
        }
        if (s2.length() == 0) {
            return s1;
        }
        //Initialize a new statistician, the sum of s1 and s2
        /*The m_total of s3 will be the sum of all the numbers in
        s1 and s2. The m_count of s3 will be the total number of 
        numbers in the union of s1 and s2. 
        */
        statistician s3;
        s3.m_total = s1.sum() + s2.sum();
        s3.m_count = s1.length() + s2.length();
        /*To determine the smallest and largest number in s3,
        * we want the smallest and largest number in the union of
        * s1 and s2.
        */
        if (s1.minimum() <= s2.minimum()) {
            s3.m_tinyest = s1.minimum();
        }
        else {
            s3.m_tinyest = s2.minimum();
        }
        if (s1.maximum() >= s2.maximum()) {
            s3.m_largest = s1.maximum();
        }
        else {
            s3.m_largest = s2.maximum();
        }
        return s3;
    }
    /*Postcondition: Return statistician that contains the same
    numbers that s does, but each number has been multiplied by the
    scale number.*/
    statistician operator *(double scale, const statistician& s) {
        //If s is empty, statistician returned will be the same
        //Return empty statistician
        if (s.length() == 0) {
            return s;
        }
        //statScale and s have the same m_count, the rest of the numbers in s will
        //be multiplied by scale
        statistician statScale;
        statScale.m_count = s.length();
        statScale.m_total = s.sum() * scale;
        //If scale is negative, the smallest and largest numbers in s will switch
        if (scale < 0) {        
            statScale.m_tinyest = s.maximum() * scale;
            statScale.m_largest = s.minimum() * scale;
        }
        else {
            statScale.m_tinyest = s.minimum() * scale;
            statScale.m_largest = s.maximum() * scale;
        }
        return statScale;
    }
    /*Postcondition: Return true is both s1 and s2 are empty. If the length is greater than zero, 
    then s1 and s2 must have the same length, mean, minimum, maximum, and sum.*/
    bool operator ==(const statistician& s1, const statistician& s2) {
        if (s1.length() == 0 && s2.length() == 0) {
            return true;
        }
        else {
            return((s1.sum() == s2.sum()) && (s1.length() == s2.length()) && (s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum()));

        }
    }
}