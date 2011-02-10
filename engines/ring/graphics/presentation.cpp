/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "ring/graphics/presentation.h"

#include "ring/base/text.h"

#include "ring/game/application.h"
#include "ring/game/puzzle.h"

#include "ring/graphics/animation.h"
#include "ring/graphics/image.h"
#include "ring/graphics/rotation.h"

#include "ring/ring.h"
#include "ring/helpers.h"

namespace Ring {

#pragma region Presentation

PresentationImage::PresentationImage() {
}

PresentationImage::~PresentationImage() {
}

#pragma endregion

#pragma region Presentation

ObjectPresentation::ObjectPresentation(Object *object) : _object(object) {
	_isShown = false;
}

ObjectPresentation::~ObjectPresentation() {
	CLEAR_ARRAY(ImageHandle, _imagePuzzle);
	CLEAR_ARRAY(Puzzle, _imagePuzzlePtr);
	CLEAR_ARRAY(AnimationImage, _animationPuzzle);
	CLEAR_ARRAY(Puzzle, _animationPuzzlePtr);
	CLEAR_ARRAY(BaseId, _layerImagePtr);
	CLEAR_ARRAY(Rotation, _layImageRotationPtr);
	CLEAR_ARRAY(BaseId, _layerAnimationRotation);
	CLEAR_ARRAY(Rotation, _layerAnimationRotationPtr);
	CLEAR_ARRAY(Animation, _layerAnimationRotationAnimation);
	CLEAR_ARRAY(Text, _textPuzzle);
	CLEAR_ARRAY(Puzzle, _textPuzzlePtr);
	CLEAR_ARRAY(Text, _textRotation);
	CLEAR_ARRAY(Rotation, _textRotationPtr);

	// Zero-out passed pointers
	_object = NULL;
}

void ObjectPresentation::addTextToPuzzle(Puzzle *puzzle, Common::String text, const Common::Point &point, FontId fontId, byte a7, byte a8, byte a9, int32 a10, int32 a11, int32 a12) {
	Text *textObject = new Text();
	textObject->init(text, point, fontId, a7, a8, a9, a10, a11, a12);
	textObject->setObjectPresentation(this);

	_textPuzzle.push_back(textObject);
	_textPuzzlePtr.push_back(puzzle);

	puzzle->addPresentationText(textObject);
}

void ObjectPresentation::addImageToPuzzle(Puzzle *puzzle, Common::String filename, const Common::Point &point, bool isActive, byte a7, uint32 priority, byte a9, LoadFrom loadFrom) {
	ImageHandle *image = new ImageHandle(filename, point, isActive, a7, priority, a9, getApp()->getCurrentZone(), loadFrom, 4, getApp()->getArchiveType());
	image->setObjectPresentation(this);

	_imagePuzzle.push_back(image);
	_imagePuzzlePtr.push_back(puzzle);

	puzzle->addPresentationImage(image);
}

void ObjectPresentation::addImageToRotation(Rotation *rotation, uint32 layer) {
	_layerImagePtr.push_back(new BaseId(layer));
	_layImageRotationPtr.push_back(rotation);
}

void ObjectPresentation::addAnimationToPuzzle(Puzzle *puzzle, Common::String filename, uint32 a4, const Common::Point &point, uint32, uint32 a8, uint32 priority, byte frameCount, uint32 a11, float a12, byte a13, LoadFrom loadFrom) {
	AnimationImage *animation = new AnimationImage();
	animation->init(filename, a4, point, 0, a8, a11, a12, 1, a13, frameCount, priority, loadFrom, getApp()->getArchiveType());
	animation->updatePresentation(this);
	if (!(a13 & 2)) {
		animation->setField20(0);
		animation->setField89();
	}

	_animationPuzzle.push_back(animation);
	_animationPuzzlePtr.push_back(puzzle);

	animation->updateCurrentImage();

	puzzle->addPresentationImage(animation->getCurrentImage());
	puzzle->addPresentationAnimation(this);
}

void ObjectPresentation::addAnimationToRotation(Rotation *rotation, uint32 layer, uint32 a3, float a4, uint32 a5) {
	Animation *animation = rotation->addPresentationAnimation(this, layer, a3, a4, a5);

	if (!(a5 & 2))
		animation->setField20(0);

	_layerAnimationRotation.push_back(new BaseId(layer));
	_layerAnimationRotationPtr.push_back(rotation);
	_layerAnimationRotationAnimation.push_back(animation);
}

void ObjectPresentation::setAnimationOnPuzzle(uint32 animationIndex, ObjectId objectId) {
	if (animationIndex >= _animationPuzzle.size())
		error("[ObjectPresentation::setAnimationOnPuzzle] Invalid animation index (was: %d, max: %d)", animationIndex, _animationPuzzle.size() - 1);

	_animationPuzzle[animationIndex]->setId(objectId);
}

void ObjectPresentation::setAnimationOnRotation(uint32 animationIndex, ObjectId objectId) {
	if (animationIndex >= _layerAnimationRotationAnimation.size())
		error("[ObjectPresentation::setAnimationOnPuzzle] Invalid animation index (was: %d, max: %d)", animationIndex, _layerAnimationRotationAnimation.size() - 1);

	_layerAnimationRotationAnimation[animationIndex]->setId(objectId);
}

void ObjectPresentation::setAnimationStartFrame(uint32 startFrame) {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->setStartFrame(startFrame);

	for (Common::Array<Animation *>::iterator it = _layerAnimationRotationAnimation.begin(); it != _layerAnimationRotationAnimation.end(); it++)
		(*it)->setStartFrame(startFrame);
}

void ObjectPresentation::setAnimationActiveFrame(uint32 activeFrame) {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->setActiveFrame(activeFrame);

	for (Common::Array<Animation *>::iterator it = _layerAnimationRotationAnimation.begin(); it != _layerAnimationRotationAnimation.end(); it++)
		(*it)->setActiveFrame(activeFrame);
}

void ObjectPresentation::setAnimationCoordinatesOnPuzzle(const Common::Point &point) {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->setCoordinates(point);
}

void ObjectPresentation::pauseAnimation() {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->pause();

	for (Common::Array<Animation *>::iterator it = _layerAnimationRotationAnimation.begin(); it != _layerAnimationRotationAnimation.end(); it++)
		(*it)->pause();
}

void ObjectPresentation::unpauseAnimation() {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->unpause();

	for (Common::Array<Animation *>::iterator it = _layerAnimationRotationAnimation.begin(); it != _layerAnimationRotationAnimation.end(); it++)
		(*it)->unpause();
}

void ObjectPresentation::pauseFrameAnimation(uint32 frame, uint32 a3, uint32 a4) {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->pauseOnFrame(frame, a3, a4);

	for (Common::Array<Animation *>::iterator it = _layerAnimationRotationAnimation.begin(); it != _layerAnimationRotationAnimation.end(); it++)
		(*it)->pauseOnFrame(frame, a3, a4);
}

void ObjectPresentation::show() {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->setTicks(g_system->getMillis());

	for (Common::Array<Animation *>::iterator it = _layerAnimationRotationAnimation.begin(); it != _layerAnimationRotationAnimation.end(); it++)
		(*it)->setTicks(g_system->getMillis());

	for (uint32 i = 0; i < _layerImagePtr.size(); i++)
		_layImageRotationPtr[i]->updateNode(*(_layerImagePtr[i]), 1);

	for (uint32 i = 0; i < _layerAnimationRotation.size(); i++)
		_layerAnimationRotationPtr[i]->updateNode(_layerAnimationRotation[i]->id(), 1);
}

void ObjectPresentation::hide() {
	for (Common::Array<AnimationImage *>::iterator it = _animationPuzzle.begin(); it != _animationPuzzle.end(); it++)
		(*it)->sub_416710();

	for (Common::Array<Animation *>::iterator it = _layerAnimationRotationAnimation.begin(); it != _layerAnimationRotationAnimation.end(); it++)
		(*it)->sub_416710();

	for (uint32 i = 0; i < _layerImagePtr.size(); i++)
		_layImageRotationPtr[i]->updateNode(*(_layerImagePtr[i]), 0);

	for (uint32 i = 0; i < _layerAnimationRotation.size(); i++)
		_layerAnimationRotationPtr[i]->updateNode(_layerAnimationRotation[i]->id(), 0);
}

void ObjectPresentation::hideAndRemove() {
	error("[ObjectPresentation::hide] Not implemented");
}

#pragma endregion

} // End of namespace Ring
