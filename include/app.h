class Application
{
protected:
    int height;
    int width;
	float nRange;
	float timeinterval;
public:
    virtual void initGraphics();
    virtual void display();
    virtual void resize(int width, int height);
	virtual void update();

	int getHeight(void);
	int getWidth(void);

	float getTimeinterval();
	void setTimeinterval(float timeint);
	Application();
 };
    

