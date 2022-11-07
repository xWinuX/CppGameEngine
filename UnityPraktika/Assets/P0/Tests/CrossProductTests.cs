using NUnit.Framework;
using UnityEngine;

namespace P0.Tests
{
    public class CrossProductTests
    {
                
        [Test]
        public void The_Magnitude_Of_The_CrossProduct_Of_Two_Vectors_Should_Be_Equal_To_The_Area_Of_A_Rectangle_Constructed_With_The_Two_Vectors()
        {
            Vector3 a = new Vector3(12f, -4f, 4.3f);
            Vector3 b = new Vector3(-2f, 0f, -0.3f);

            Vector3 crossProduct  = Vector3.Cross(a, b);
            
            float   rectangleArea = a.magnitude * b.magnitude;

            UnityEngine.Assertions.Assert.AreApproximatelyEqual(crossProduct.magnitude, Mathf.Sqrt(rectangleArea), 0.1f);
        }
    }
}