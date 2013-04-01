#include "SDLGui.h"

#if _SDLGUI_VER_ != 128
	#warning Invalid SDLGui version
#endif

void GUIDrawBorder(SDL_Surface *dst, int x1, int y1, int x2, int y2, Uint32 outLeft, Uint32 inLeft, Uint32 outRight, Uint32 inRight, bool topLeft=false);

void GUIDropDown::Draw(SDL_Surface *dst){
	boxColor(dst,posX1,posY1,posX2,posY2,0xFFFFFFFF);
	GUIDrawBorder(dst,posX1,posY1,posX2,posY2,0x404040FF,0x808080FF,0xFFFFFFFF,0,true);
	selectedText.Blit(dst,posX1+3,posY1+2,posX2-posX1-3,posY2-posY1-2,false,true);
	boxColor(dst,arrX1,arrY1,arrX2,arrY2,0xD4D0C8FF);
	if(isPressed)GUIDrawBorder(dst,arrX1,arrY1,arrX2,arrY2,0x404040FF,0x808080FF,0xFFFFFFFF,0,true);
	else GUIDrawBorder(dst,arrX1,arrY1,arrX2,arrY2,0xFFFFFFFF,0,0x404040FF,0x808080FF);
	filledTrigonColor(dst,triX1,triY1,triX2,triY2,triX3,triY3,0x00000080);
	if(listBox.doDraw&&!hasRegistered)listBox.Draw(dst);
}

void GUIDropDown::StyleConstruct(){

}

void GUIListBox::Draw(SDL_Surface *dst){
	boxColor(dst,posX1,posY1,posX2,posY2,0xFFFFFFFF);
	if(showSelectionBox)boxColor(dst,selX1,selY1,selX2,selY2,0x6666FFFF);
	renderedText.Blit(dst,textX1,textY1,textX2-textX1,textY2-textY1,false,false,curOffX,curOffY);
	GUIDrawBorder(dst,posX1,posY1,posX2,posY2,0x404040FF,0x808080FF,0xFFFFFFFF,0,true);
	scroll.Draw(dst);
}

void GUIListBox::StyleConstruct(){
	textBorderUp=2; textBorderLeft=2; textBorderDown=0; textBorderRight=0;
	textSliderThick=14;
}

void GUITextBox::Draw(SDL_Surface *dst){
	boxColor(dst,posX1,posY1,posX2,posY2,fontBackColor);
	renderedText.Blit(dst,textX1,textY1,textX2-textX1,textY2-textY1,false,false,curOffX,curOffY);
	GUIDrawBorder(dst,posX1,posY1,posX2,posY2,0x404040FF,0x808080FF,0xFFFFFFFF,0,true);
	if(CursorBlink())boxColor(dst,curDrawX,curDrawY,curDrawX,curDrawY+curDrawH,0x330000FF);
	if(showPointer){
		vlineColor(dst,mouseX,mouseY-6,mouseY+6,0x00000080);
		hlineColor(dst,mouseX-3,mouseX+3,mouseY-7,0x00000080);
		hlineColor(dst,mouseX-3,mouseX+3,mouseY+7,0x00000080);
	}
	if(showScroll){
		scrollX.Draw(dst);
		scrollY.Draw(dst);
	}
}

void GUITextBox::StyleConstruct(){
	textBorderUp=2; textBorderLeft=2; textBorderDown=0; textBorderRight=0;
	textSliderThick=15;
}

void GUIScrollBar::Draw(SDL_Surface *dst){
	boxColor(dst,trackX1,trackY1,trackX2,trackY2,0xE0E0E0FF);
	GUIDrawBorder(dst,trackX1,trackY1,trackX2,trackY2,0x808080FF,0,0xFFFFFFFF,0);

	if(arrowW>0){
		boxColor(dst,arrAX1,arrAY1,arrAX2,arrAY2,0xD4D0C8FF);
		boxColor(dst,arrBX1,arrBY1,arrBX2,arrBY2,0xD4D0C8FF);

		if(arrADown)GUIDrawBorder(dst,arrAX1,arrAY1,arrAX2,arrAY2,0x404040FF,0x808080FF,0xFFFFFFFF,0,true);
		else GUIDrawBorder(dst,arrAX1,arrAY1,arrAX2,arrAY2,0xFFFFFFFF,0,0x404040FF,0x808080FF);
		if(arrBDown)GUIDrawBorder(dst,arrBX1,arrBY1,arrBX2,arrBY2,0x404040FF,0x808080FF,0xFFFFFFFF,0,true);
		else GUIDrawBorder(dst,arrBX1,arrBY1,arrBX2,arrBY2,0xFFFFFFFF,0,0x404040FF,0x808080FF);

		filledTrigonColor(dst,triAX1,triAY1,triAX2,triAY2,triAX3,triAY3,0x00000080);
		filledTrigonColor(dst,triBX1,triBY1,triBX2,triBY2,triBX3,triBY3,0x00000080);
	}

	if(!isDisabled){
		boxColor(dst,slidX1,slidY1,slidX2,slidY2,0xD4D0C8FF);
		GUIDrawBorder(dst,slidX1,slidY1,slidX2,slidY2,0xFFFFFFFF,0,0x404040FF,0x808080FF);
	}
}

void GUIScrollBar::StyleConstruct(){

}

void GUIButton::Draw(SDL_Surface *dst){
	boxColor(dst,posX1,posY1,posX2,posY2,0xD4D0C8FF);
	renderedText.Blit(dst,posX1,posY1,posX2-posX1,posY2-posY1,true,true);
	if(!isDisabled){
		if(isPressed&&isHovered)GUIDrawBorder(dst,posX1,posY1,posX2,posY2,0x404040FF,0x808080FF,0xFFFFFFFF,0,true);
		else GUIDrawBorder(dst,posX1,posY1,posX2,posY2,0xFFFFFFFF,0,0x404040FF,0x808080FF);
	}else{
		boxColor(dst,posX1,posY1,posX2,posY2,0xFFFFFFA0);
		//rectangleColor(dst,posX1,posY1,posX2,posY2,0x404040FF);
		GUIDrawBorder(dst,posX1,posY1,posX2,posY2,0xFFFFFFFF,0,0x404040FF,0x808080FF);
	}
}

void GUIButton::StyleConstruct(){
	textColor.r=0x00; textColor.g=0x00; textColor.b=0x00; textColor.unused=0xFF;
}

void GUICheckBox::Draw(SDL_Surface *dst){
	if(isCircle){
		int rad = ((posX2-posX1<posY2-posY1)?(posX2-posX1):(posY2-posY1))-7;
		filledCircleColor(dst,(posX1+posX2)/2,(posY1+posY2)/2,rad,0xFFFFFFFF);
		arcColor(dst,(posX1+posX2)/2,(posY1+posY2)/2,rad,135,315,0x000000FF);
		arcColor(dst,(posX1+posX2)/2,(posY1+posY2)/2,rad+1,135,315,0x808080FF);
		arcColor(dst,(posX1+posX2)/2,(posY1+posY2)/2,rad,315,135,0xD4D0C8FF);
		arcColor(dst,(posX1+posX2)/2,(posY1+posY2)/2,rad+1,315,135,0xFFFFFFFF);
		if(isChecked)filledCircleColor(dst,(posX1+posX2)/2,(posY1+posY2)/2,rad-3,0x000000FF);
	}else{
		boxColor(dst,posX1,posY1,posX2,posY2,0xFFFFFFFF);
		GUIDrawBorder(dst,posX1,posY1,posX2,posY2,0x808080FF,0x404040FF,0xFFFFFFFF,0xD4D0C8FF);
		if(isChecked){
			int tickX=((posX2+posX1)/2)-2,tickY=((posY2+posY1)/2)-3; Uint32 clr=0x000000FF;
			boxColor(dst,tickX+1,tickY+4,tickX+3,tickY+5,clr);
			boxColor(dst,tickX+4,tickY+2,tickX+5,tickY+3,clr);
			vlineColor(dst,tickX,tickY+2,tickY+4,clr);
			vlineColor(dst,tickX+6,tickY,tickY+2,clr);
			pixelColor(dst,tickX+1,tickY+3,clr);
			pixelColor(dst,tickX+3,tickY+3,clr);
			pixelColor(dst,tickX+4,tickY+4,clr);
			pixelColor(dst,tickX+5,tickY+1,clr);
			pixelColor(dst,tickX+2,tickY+6,clr);
		}
	}
}

void GUICheckBox::StyleConstruct(){

}

void GUILabel::Draw(SDL_Surface *dst){
	text.Blit(dst,posX1,posY1,posX2-posX1,posY2-posY1,centerX,centerY);
}

void GUILabel::StyleConstruct(){

}

void GUIDrawBorder(SDL_Surface *dst, int x1, int y1, int x2, int y2, Uint32 outLeft, Uint32 inLeft, Uint32 outRight, Uint32 inRight, bool topLeft){
	if(outLeft!=0){
		vlineColor(dst,x1,y1,y2-1,outLeft);
		hlineColor(dst,x1,x2-1,y1,outLeft);
	}
	if(inLeft!=0){
		vlineColor(dst,x1+1,y1+1,y2-2,inLeft);
		hlineColor(dst,x1+1,x2-2,y1+1,inLeft);
	}
	if(outRight!=0){
		vlineColor(dst,x2,y1+1,y2,outRight);
		hlineColor(dst,x1+1,x2-1,y2,outRight);
	}
	if(inRight!=0){
		vlineColor(dst,x2-1,y1+2,y2-1,inRight);
		hlineColor(dst,x1+2,x2-2,y2-1,inRight);
	}
	if(topLeft){
		outRight=outLeft;
		inRight=inLeft;
	}
	pixelColor(dst,x2,y1,outRight);
	pixelColor(dst,x1,y2,outRight);
	pixelColor(dst,x1+1,y2-1,inRight);
	pixelColor(dst,x2-1,y1+1,inRight);
}

