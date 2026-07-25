/*
** ETIB PROJECT, 2026
** xider
** File description:
** renderable
*/

#include <utility/graphic/renderable.hpp>

namespace utility::graphic
{
	Renderable::Renderable(const PoseF &pose, const Color32Bit &color)
		: _pose(pose)
		, _color(color)
	{
	}

	/////////////
	// Getters //
	/////////////

	const PoseF &Renderable::getPose(void) const
	{
		return _pose;
	}

	const Color32Bit &Renderable::getColor(void) const
	{
		return _color;
	}

	std::vector<std::shared_ptr<Mesh>> Renderable::getMeshes() const
	{
		return _meshes;
	}

	/////////////
	// Setters //
	/////////////

	Renderable &Renderable::setPose(const PoseF &pose)
	{
		_pose = pose;
		return *this;
	}

	void Renderable::setPose(PoseF &&pose)
	{
		_pose = std::move(pose);
	}

	Renderable &Renderable::setColor(const Color32Bit &color)
	{
		_color = color;
		return *this;
	}

	void Renderable::setColor(Color32Bit &&color)
	{
		_color = std::move(color);
	}

}	 // namespace utility::graphic