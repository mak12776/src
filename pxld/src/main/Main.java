package main;

import java.io.IOException;

import pxld.Image;
import pxld.Picture.MapFunction;
import pxld.types.ColorMode;

public class Main 
{
	public static void main(String[] args) throws IOException 
	{
		ColorMode mode = ColorMode.RGB;
		
		MapFunction func = new MapFunction() 
		{
			@Override
			public void map(int x, int y, byte[] data, int offset) 
			{
				
			}
		};
		
		Image image = new Image(ColorMode.RGB, 300, 300, func);
		
		image.save("picture.img");
	}
}
