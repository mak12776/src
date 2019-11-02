
package PACKAGE_NAME;

public class TYPE_POINT
{
	public TYPE x;
	public TYPE y;

	public TYPE_POINT()
	{
		this.x = ZERO;
		this.y = ZERO;
	}

	public TYPE_POINT(TYPE x, TYPE y)
	{
		this.x = x;
		this.y = y;
	}

	public void add(TYPE a)
	{
		this.x += a;
		this.y += a;
	}

	public void add(TYPE x, TYPE y)
	{
		this.x += x;
		this.y += y;
	}

	public TYPE_POINT copy()
	{
		return new TYPE_POINT(x, y);
	}

	public boolean isNatural()
	{
		return (this.x > ZERO) && (this.y > ZERO);
	}

	public void xLimit(TYPE min, TYPE max)
	{
		if (x < min)
		{
			x = min;
		}
		else if (x > max)
		{
			x = max;
		}
	}

	public void yLimit(TYPE min, TYPE max)
	{
		if (y < min)
		{
			y = min;
		}
		else if (y > max)
		{
			y = max;
		}
	}

	public void limit(TYPE xMin, TYPE yMin, TYPE xMax, TYPE yMax)
	{
		xLimit(xMin, xMax);
		yLimit(yMin, yMax);
	}
}
