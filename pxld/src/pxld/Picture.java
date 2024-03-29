package pxld;

import pxld.types.ColorMode;

public interface Picture 
{
	public byte[] getData();
	
	public ColorMode getColorMode();
	public int getColorWidth();
	
	public int width();
	public int height();
	
	public interface MapFunction
	{
		void map(int x, int y, byte[] data, int offset);
	}
	
	public void draw(byte[] colorData);
	
	public void drawPicture(int x, int y, Picture picture);
	
	public void map(MapFunction map);
}
