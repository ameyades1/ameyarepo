class CCircle
{
	float radius;
public:
	CCircle();
	~CCircle();

	// R, theta
	CCircle(float radius);

	float CircleArea()
	{
		return 3.14 * radius * radius;
	}

	float Circumference()
	{
		return 2 * 3.14 * radius;
	}

};
