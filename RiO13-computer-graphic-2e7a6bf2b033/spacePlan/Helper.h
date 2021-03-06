#pragma once
#include"texture.h"
//#include "Player.h"
//#include "Draft.h"

namespace helper {
	typedef struct {
		int type;
		char *name;
	}Tex;
	enum {
		EARTH = 0, 
		ALFRED,
		FON,
		DRAFT,
		STEP_AL,
		STEP_TWO_AL,
		ROCKET,
		ASTEROID,
		FOG,
		STARS
	};
	static int sault = 0;
	double static m_width = 0;
	double static m_height = 0;
	 
	TextureImage static textures[10];
	std::vector<Tex> static nameTextures;
	static void loadTexture(int i, char * str, int type)
	{
		CTexture *Texture = new CTexture();
		Texture->LoadTexture(type, str, &textures[i], i);
	}
	
	static void fillTextures() {
		Tex first;
		first.name = "zeml22.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);
		first.name = "alf110.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);
<<<<<<< HEAD
		first.name = "fon101.png";
		first.type = IL_PNG;
=======
		first.name = "fon101.tga";
		first.type = IL_TGA;
>>>>>>> origin/master
		nameTextures.push_back(first);
		//std::string draft = "green.bmp";
		first.name = "musor101.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);

		first.name = "spr1.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);
		first.name = "spr1.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);

		first.name = "rocket.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);
		first.name = "cometa.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);

<<<<<<< HEAD
		first.name = "fon103.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);

		first.name = "fon102.png";
=======
		first.name = "data/fon22.png";
		first.type = IL_PNG;
		nameTextures.push_back(first);

		first.name = "data/fon33.png";
>>>>>>> origin/master
		first.type = IL_PNG;
		nameTextures.push_back(first);
		for (size_t i = 0; i < nameTextures.size(); ++i)
		{
			helper::loadTexture(i, nameTextures.at(i).name, nameTextures.at(i).type);
		}
	}

	/*void collission(CPlayer &m_player, std::vector<CDraft> &drafts)
	{

		for (size_t i = 0; i < drafts.size(); ++i) {
			if (((drafts.at(i).getXCenter() > m_player.getLeft() && drafts.at(i).getXCenter() < m_player.getRight())
				&& drafts.at(i).getYCenter() < m_player.getTop() && drafts.at(i).getYCenter() > m_player.getBottom()))
			{
				drafts.at(i).kill();
			}
		}

	}**/

}

