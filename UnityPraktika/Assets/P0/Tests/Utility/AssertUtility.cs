using NUnit.Framework;

namespace P0.Tests.Utility
{
    public class AssertUtility
    {
        public static void AssertBetween(float value, float minValue, float maxValue)
        {
            Assert.LessOrEqual(value, maxValue);
            Assert.GreaterOrEqual(value, minValue);
        }

        public static void AssertNormalized(float value) { AssertBetween(value, -1, 1); }
    }
}