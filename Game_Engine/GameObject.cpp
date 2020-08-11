//GameObject Source File

#include "GameObject.h"

//Loader class constructor
Loader::Loader(bool isAccelerating, bool flipable, int parameterX, int parameterY, int parameterSourceWidth, int parameterSourceHeight, 
	int parameterDestinationWidth, int parameterDestinationHeight, float parameterRow, float parameterFrame, float parameterLeftLastFrame, 
	int animationFactor, std::string parameterTextureID, std::string parameterPath, int parameterFlippedLeft, int parameterFlippedTop, int flippedLastFrame,
	std::string flipTextureID, std::string parameterflipPath)
{
	x = parameterX;
	y = parameterY;
	sourceRectWidth = parameterSourceWidth;
	sourceRectHeight = parameterSourceHeight;
	destinationRectWidth = parameterDestinationWidth;
	destinationRectHeight = parameterDestinationHeight;
	row = parameterRow;
	frame = parameterFrame;
	leftLastFrame = parameterLeftLastFrame;
	textureID = parameterTextureID;
	path = parameterPath;
	isAcceleratingGameObject = isAccelerating;
	specialAnimationFactor = animationFactor;
	flippedLeft = parameterFlippedLeft;
	flippedTop = parameterFlippedTop;
	flippedLeftOfLastFrame = flippedLastFrame;
	flippingRequired = flipable;
	flippedPath = parameterflipPath;
	flippedTextureID = flipTextureID;
}

//Loader 2nd constructor
Loader::Loader(std::string parameterPath, std::string id, int width, int height, float scaleX, float scaleY)
{
	path = parameterPath;
	textureID = id;
	sourceRectWidth = width;
	sourceRectHeight = height;
	destinationRectWidth = scaleX;
	destinationRectHeight = scaleY;
	x = y = specialAnimationFactor = flippedLeft = flippedTop = flippedLeftOfLastFrame = 0;
	row = frame = leftLastFrame = 0.0f;
	isAcceleratingGameObject = false;
	flippingRequired = false;
	flippedPath = flippedTextureID = "\0";
}

//Returns x
int Loader::GetX() const
{
	return x;
}

//Returns y
int Loader::GetY() const
{
	return y;
}

//Returns source rect width
int Loader::GetSourceWidth() const
{
	return sourceRectWidth;
}

//Returns source rect height
int Loader::GetSourceHeight() const
{
	return sourceRectHeight;
}

//Returns destination rect width
int Loader::GetDestinationWidth() const
{
	return destinationRectWidth;
}

//Returns destination rect height
int Loader::GetDestinationHeight() const
{
	return destinationRectHeight;
}

//Returns special animation factor
int Loader::GetAnimationFactor() const
{
	return specialAnimationFactor;
}

//Returns left of first frame of flipped sprite
int Loader::GetFlippedLeft() const
{
	return flippedLeft;
}

//Returns top of first frame of flipped sprite
int Loader::GetFlippedTop() const
{
	return flippedTop;
}

//Returns last frame of flipped animation
int Loader::GetFlippedLastFrame() const
{
	return flippedLeftOfLastFrame;
}

//Returns row of first frame of animation
float Loader::GetRow() const
{
	return row;
}

//Returns first frame of animation
float Loader::GetFrame() const
{
	return frame;
}

//Return the left side of last frame of animation
float Loader::GetLeftLastFrame() const
{
	return leftLastFrame;
}

//Returns texture id
std::string Loader::GetTextureID() const
{
	return textureID;
}

//Returns spritesheet path
std::string Loader::GetPath() const
{
	return path;
}

//Returns flipped texture ID
std::string Loader::GetFlippedTextureID() const
{
	return flippedTextureID;
}

//Returns flipped spritesheet
std::string Loader::GetFlippedPath() const
{
	return flippedPath;
}

//Returns if gameobject is of accelerating type or not
bool Loader::GetObjectType() const
{
	return isAcceleratingGameObject;
}

//Returns if object can be flipped during gameplay
bool Loader::GetFlipStatus() const
{
	return flippingRequired;
}

//Constructor for Abstract GameObject class
Abstract_Game_Object::Abstract_Game_Object(const Loader* parameters)
{
	//Constructor for Abstract_Game_Object 
}

//Constructor for GameObject class
GameObject::GameObject(const Loader* parameters)
{
	position.SetX(parameters->GetX());
	position.SetY(parameters->GetY());
	destinationRectWidth = parameters->GetDestinationWidth();
	destinationRectHeight = parameters->GetDestinationHeight();
	textureID = parameters->GetTextureID();
	canBeFlipped = parameters->GetFlipStatus();
	TextureManager::Instance()->Load(parameters->GetPath(), parameters->GetTextureID());
	if (canBeFlipped)
	{
		flippedTextureID = parameters->GetFlippedTextureID();
		TextureManager::Instance()->Load(parameters->GetFlippedPath(), parameters->GetFlippedTextureID());
	}
	currentFrame = parameters->GetFrame();
	leftOfLastFrame = parameters->GetLeftLastFrame();
	time = 0.0f;
	frameSpeed = 0.05f;
	velocity.SetX(0);
	velocity.SetY(0);
	isAcceleratingGameObject = parameters->GetObjectType();
	sourceRect.left = currentFrame;
	sourceRect.top = parameters->GetRow();
	sourceRect.width = parameters->GetSourceWidth();
	sourceRect.height = parameters->GetSourceHeight();
	specialAnimationFactor = parameters->GetAnimationFactor();
	currentFlippedFrame = parameters->GetFlippedLeft();
	flippedLastFrame = parameters->GetFlippedLastFrame();
	flippedSourceRect.left = currentFlippedFrame;
	flippedSourceRect.top = parameters->GetFlippedTop();
	flippedSourceRect.width = sourceRect.width;
	flippedSourceRect.height = sourceRect.height;
	collider = TextureManager::Instance()->GetCollider(parameters->GetTextureID());
}

//To draw sprite 
void GameObject::Draw(RenderWindow* window)
{
	if(velocity.GetX() < 0 && canBeFlipped)
		TextureManager::Instance()->Animate(flippedTextureID, (int)position.GetX(), (int)position.GetY(), flippedSourceRect, window,
			destinationRectWidth, destinationRectHeight);
	else 
		TextureManager::Instance()->Animate(textureID, (int)position.GetX(), (int)position.GetY(), sourceRect, window, destinationRectWidth,
			destinationRectHeight);
}

//To draw still images
void GameObject::DrawStill(RenderWindow* window)
{
	TextureManager::Instance()->Draw(textureID, (int)position.GetX(), (int)position.GetY(), sourceRect.width, sourceRect.height, 0, 0, window,
		destinationRectWidth, destinationRectHeight);
}

//Custom update function for gameobjects
void GameObject::Update(float dtAsSeconds)
{
	collider = TextureManager::Instance()->GetCollider(textureID);
	if (time > frameSpeed)
	{
		if (velocity.GetX() < 0 && canBeFlipped)
		{
			if (flippedSourceRect.left <= flippedLastFrame)
				flippedSourceRect.left = currentFlippedFrame;
			else
				flippedSourceRect.left -= flippedSourceRect.width + specialAnimationFactor;
		}
		else
		{
			if (sourceRect.left >= leftOfLastFrame)
				sourceRect.left = currentFrame;
			else
				sourceRect.left += sourceRect.width + specialAnimationFactor;
		}
		if (isAcceleratingGameObject)
			velocity += acceleration;
		position += velocity;
		time = 0.0f;
	}
	else
		time += dtAsSeconds;
}

//To clean garbage after use
void GameObject::Clean()
{
	//GameObject Clean Method to delete garbage
}

//Returns gameobject's position
Vector2D& GameObject::GetPosition()
{
	return position;
}

//Returns gameobject's width
int GameObject::GetWidth()
{
	return sourceRect.width;
	//return destinationRectWidth;
}

//Returns gameobject's height
int GameObject::GetHeight()
{
	return destinationRectHeight;
}

//Return Collider
FloatRect* GameObject::GetCollider()
{
	return &collider;
}

//Constructor for subdivision of GameObject class (Player class)
Player::Player(const Loader* parameters) : GameObject(parameters)
{
	//Don't tamper with this method
}

void Player::HandleInput()
{
	if (InputHandler::Instance()->JoysticksInitialized())
	{
		if (InputHandler::Instance()->XValue(0, 1) > 0 || InputHandler::Instance()->XValue(0, 1) < 0)
			velocity.SetX(1 * InputHandler::Instance()->XValue(0, 1));
		if (InputHandler::Instance()->YValue(0, 1) > 0 || InputHandler::Instance()->YValue(0, 1) < 0)
			velocity.SetY(1 * InputHandler::Instance()->YValue(0, 1));
		if (InputHandler::Instance()->XValue(0, 2) > 0 || InputHandler::Instance()->XValue(0, 2) < 0)
			velocity.SetX(1 * InputHandler::Instance()->XValue(0, 2));
		if (InputHandler::Instance()->YValue(0, 2) > 0 || InputHandler::Instance()->YValue(0, 2) < 0)
			velocity.SetX(1 * InputHandler::Instance()->YValue(0, 2));
	}
	else
	{
		if (InputHandler::Instance()->GetMouseButtonState(LEFT))
		{
			//Shoot Bullet
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
			velocity.SetX(40);
		if (Keyboard::isKeyPressed(Keyboard::A))
			velocity.SetX(-40);
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			//Jump
		}
	}
}

//To draw specifically player sprite
void Player::Draw(RenderWindow* window)
{
	GameObject::Draw(window);
}

//To update specifically player gameObject
void Player::Update(float dtAsSeconds)
{
	velocity.SetX(0);
	velocity.SetY(0);
	if (isAcceleratingGameObject)
		acceleration.SetX(1);
	HandleInput();
	GameObject::Update(dtAsSeconds);
}

//To specifically delete player
void Player::Clean()
{
	//Delete garbage
}

//Constructor for subdivision of GameObject class (Enemy class)
Enemy::Enemy(const Loader* parameters) : GameObject(parameters)
{
	velocity.SetX(-20);
}

//To draw specifically enemies
void Enemy::Draw(RenderWindow* window)
{
	GameObject::Draw(window);
}

//To specifically update enemies' behaviour
void Enemy::Update(float dtAsSeconds)
{
	GameObject::Update(dtAsSeconds);
}

//To specifically delete enemies
void Enemy::Clean()
{
	//Delete garbage
}

AnimatedGraphic::AnimatedGraphic(const Loader* parameters, int parameterAnimationSpeed) : GameObject(parameters)
{
	animationSpeed = parameterAnimationSpeed;
}

void AnimatedGraphic::Update(float dtAsSeconds)
{
	//Calculate current frame
}