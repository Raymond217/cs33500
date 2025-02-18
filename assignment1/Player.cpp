#include "Player.hpp"

Player::Player(const std::string& name, const Inventory& inventory = Inventory()):name_(name),inventory_(inventory)
{

}
std::string Player::getName() const
{
    return name_;
}
Inventory& Player::getInventoryRef()
{
    return inventory_;
}
Player::Player(const Player& rhs):name_(rhs.name_),inventory_(rhs.inventory_)
{
    
}
Player::Player(Player&& rhs):name_(std::move(rhs.name_)),inventory_(std::move(rhs.inventory_))
{

}
Player& Player::operator=(const Player& rhs)
{
    if (this != &rhs)
    {
        name_= rhs.name_;
        inventory_ = rhs.inventory_;

    }
    return *this;
}
Player& Player::operator=(Player&& rhs)
{
    if (this != &rhs)
    {
        name_=std::move(rhs.name_);
        inventory_= std::move(rhs.inventory_);
    }
    return *this;
}