class WallLaw
{
public:

    static void Apply(double& rValue)
    {
        rValue += 10;
    }
};

class WallLawDerived : public WallLaw
{
public:
    static void Apply(double& rValue)
    {
        rValue += 100;
    }
};