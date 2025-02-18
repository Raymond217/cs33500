#include "Inventory.hpp"
Inventory::Inventory(const std::vector<std::vector<Item>>& items,Item* equipped):inventory_grid_(items),equipped_(equipped),weight_(0),item_count_(0)
{
    for (auto& row:inventory_grid_)
       for (auto& item:row)
       if (item.type_!=0){
         weight_+= item.weight_;
         item_count_++;
       }
}
Item* Inventory::getEquipped() const
{
    return equipped_;
}
void Inventory::equip(Item* itemToEquip)
{
    equipped_ = itemToEquip;
}
void Inventory::discardEquipped()
{
   equipped_ = nullptr;
}
std::vector<std::vector<Item>> Inventory::getItems() const
{
    return inventory_grid_;
}
float Inventory::getWeight() const
{
    return weight_;
}
size_t Inventory::getCount() const
{
    return item_count_;
}
Item Inventory::at(const size_t& row, const size_t& col) const
{
    if (row<0||col<0){
        throw std::out_of_range("Index out of bounds in inventory grid");
    }
    if (row>=inventory_grid_.size()||col>=inventory_grid_[row].size()){
        throw std::out_of_range("Index out of bounds in inventory grid");

    }
    return inventory_grid_[row][col];
}
bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup)
{
    if (row<0||col<0){
        throw std::out_of_range("Index out of bounds in inventory grid");
    }
    if (row>=inventory_grid_.size()||col>=inventory_grid_[row].size()){
        throw std::out_of_range("Index out of bounds in inventory grid");
    }
    if (inventory_grid_[row][col].type_ ==0)
     return false;

    inventory_grid_[row][col] = pickup; // Store item
    item_count_++;
    weight_ += pickup.weight_; // Assuming Item has `getWeight()`
    return true;
}
Inventory::Inventory(const Inventory& rhs):inventory_grid_(rhs.inventory_grid_),weight_(rhs.weight_), item_count_(rhs.item_count_)
{
    if (rhs.equipped_) {
        equipped_ = new Item(*rhs.equipped_); // Deep copy equipped item
    } else {
        equipped_ = nullptr;
    }
}
Inventory::Inventory(Inventory&& rhs):inventory_grid_(std::move(rhs.inventory_grid_)),equipped_(rhs.equipped_),weight_(rhs.weight_),item_count_(rhs.item_count_)
{
    rhs.equipped_=nullptr;
    rhs.weight_=0;
    rhs.item_count_=0;
    rhs.inventory_grid_.clear();
}
Inventory& Inventory::operator=(const Inventory& rhs)
{
    if (this != &rhs){
        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        delete equipped_;
        equipped_= nullptr;
        if (rhs.equipped_ != nullptr)
           equipped_ = new Item(*rhs.equipped_);
    }
    return *this;    
}
Inventory& Inventory::operator=(Inventory&& rhs)
{
    if (this != &rhs){
        delete equipped_;
        inventory_grid_ = std::move(rhs.inventory_grid_);
        equipped_= rhs.equipped_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        rhs.equipped_ = nullptr;
        rhs.weight_= 0;
        rhs.item_count_=0;
        rhs.inventory_grid_.clear();
    }
    return *this;
}
Inventory::~Inventory()
{
    delete equipped_;
    equipped_ = nullptr;
}