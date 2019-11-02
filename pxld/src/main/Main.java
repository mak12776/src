package main;

import java.io.IOException;

import examples.ImageGenerators;
import pxld.Image;

public class Main 
{
	public static void main(String[] args) throws IOException 
	{
		Image image = ImageGenerators.image1(300, 300);
		
		image.save("picture.img");
	}
}
