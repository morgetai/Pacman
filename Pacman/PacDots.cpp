#include"PacDots.h"
#include<algorithm>
#include"Dot.h"
#include"Primitives.h"
#include"Map.h"
#include"Help.h"
#include"InteractiveObjEngine.h"
#include"DefaultValues.h"

PacDots::PacDots(std::vector<Dot> _dots, std::shared_ptr<SDL_Renderer> r) :
	dot_image(std::make_unique<Image>(DefaultValues::BigDotWeight, DefaultValues::BigDotHeight,
		0, //x
		0, //y
		r,
		DefaultValues::DotImage)),
	dots(std::move(_dots))
{
	//x sort
	std::sort(dots.begin(), dots.end(), [this](const Dot& a, const Dot& b)
	{
		return a.get_rect().x < b.get_rect().x;
	});

	//
	eaten_dots.assign(dots.size(),false);


	int accumulate = 0;
	//y sort
	for (int x = DefaultValues::MapShiftX; x <= DefaultValues::MapWidthInPixels + DefaultValues::MapShiftX; )
	{
		std::pair<Dots::iterator, Dots::iterator> range = 
			std::equal_range(dots.begin(), dots.end(), x, cmp_rect_x<Dot>());
		//
		if (range.first != range.second)
		{

			//sorting y
			std::sort(range.first, range.second, [this](Dot& a, Dot& b)
			{
				return a.get_rect().y < b.get_rect().y;
			});

		}
		x += DefaultValues::TileWidth/2;
	}

	//setting big dots
	Rand_int ri(0, static_cast<unsigned>(dots.size() - 1));

	for (int i = 0; i < 4; ++i)
	{
		dots[ri()].set_big_dot();
	}
}

/**
* @brief render dots
* @note
* @retval
*/
void PacDots::render()
{
	for (int i = 0; i < dots.size(); ++i)
	{
		if (!eaten_dots[i])
		{
			dot_image->set_rect(dots[i].get_rect());
			dot_image->render();
		}
	}
}

/**
* @brief check collision with dots and fruits
* @note
* @param1 pacman rectangle
* @retval ObjectCollisonType
*/
ObjectCollisonType PacDots::check_collision(SDL_Rect obj)
{
	/*set upper*/
	Dots::iterator upper = std::upper_bound(dots.begin(), dots.end(), obj.x + DefaultValues::TileWidth,[]
	(int x, const Dot& d)
	{
		return d.get_pos().x > x;
	});
	/**/
	if (upper == dots.end())
		upper = dots.end() - 1;

	/*set lower*/
	Dots::iterator lower = std::lower_bound(dots.begin(), dots.end(), obj.x - DefaultValues::TileWidth, []
	(const Dot& d,int x)
	{
		return d.get_pos().x < x;
	});

	/*find collision*/
	for (; lower <= upper; ++lower)
	{
		if (SDL_HasIntersection(&obj, &lower->get_rect()))
		{
			if (!eaten_dots[lower - dots.begin()])
			{
				eaten_dots[lower - dots.begin()] = true;

				if (lower->get_rect().w == DefaultValues::BigDotWeight)

					return ObjectCollisonType::BIG_DOT_EATEN;
				else
					return ObjectCollisonType::DOT_EATEN;
			}
		}	
	}
	/*none collision was found*/
	return ObjectCollisonType::NONE_COLLISION;
};

/**
* @brief reset dots
* @note
* @retval
*/
void PacDots::reset()
{
	for (std::vector<bool>::iterator it = eaten_dots.begin(); it != eaten_dots.end(); ++it)
	{
		*it = false;
	}

	/*discard previous beg dots*/
	std::for_each(dots.begin(), dots.end(), [](Dot& d)
	{
		if (d.get_rect().w == DefaultValues::BigDotWeight)
		{
			d.discard_big_dot();
		}
	});

	//setting new big dots
	Rand_int ri(0, static_cast<unsigned>(dots.size() - 1));

	for (int i = 0; i < 4; ++i)
	{
		dots[ri()].set_big_dot();
	}
}

/**
* @brief return current number of dots
* @note
* @retval number of dots
*/
size_t PacDots::size()
{
	return dots.size();
}