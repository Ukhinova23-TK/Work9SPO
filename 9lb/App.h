#pragma once
#ifndef APP_H
#define APP_H

struct App
{
	char name[100];
	char prouzvod[100];
	double razmer;
	double zena;
	struct App *right;
	struct App *left;
	bool Sort(App* app)
	{
		if (this->razmer>app->razmer)
		{
			return true;
		}
		else if (this->razmer<app->razmer)
		{
			return false;
		}
		else
		{
			if (strcmp(this->name, app->name) > 0)
			{
				return true;
			}
			else if (strcmp(this->name, app->name) < 0)
			{
				return false;
			}
			else
			{
				if ((strcmp(this->prouzvod, app->prouzvod)) && (this->zena == app->zena))
				{
					throw 1;
				}
				else return true;
			}
		}
	}
};

#endif