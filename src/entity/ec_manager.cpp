#include "ec_manager.hpp"

using namespace entity;

ECManager::ECManager() {
    // allocate a predefined number of entities to prevent reallocating
    // constantly
    this->entities.reserve(1024);
    // NOTE: This is just an estimate
}

Entity *ECManager::instantiate_entity(
    const std::vector<ECComponent*> &components) {
    size_t entity_id;

    // check for unfilled slots and populate them with the entity
    if (this->free_slots.size() > 0) {
        entity_id = this->free_slots.back();

        // remove this index from free slots since we've populated it
        this->free_slots.pop_back();
    } else {
        entity_id = this->entities.size();
    }

    // create the entity
    Entity *entity = new Entity;
    entity->id = entity_id;
    entity->components = components;

    // initialize all entity components
    for (ECComponent *component : entity->components) {
        component->init(entity);
    }

    // add this ID to the list of valid IDs that we update when ticked
    this->valid_entity_ids.push_back(entity_id);

    // add the entity to the entity vector
    this->entities.push_back(entity);
    return entity;
}

void ECManager::deallocate(Entity *entity) {
    // deallocate all entity components
    for (ECComponent *component : entity->components) {
        delete component;
    }

    // delete the entities allocated data
    delete entity;

    // mark the entities position as overwriteable
    this->free_slots.push_back(entity->id);
}

void ECManager::tick() {
    for (size_t id : this->valid_entity_ids) {
        Entity *entity = this->entities[id];
        for (ECComponent *component : entity->components) {
            component->tick(entity);
        }
    }
}

void ECManager::update() {
    for (size_t id : this->valid_entity_ids) {
        Entity *entity = this->entities[id];
        for (ECComponent *component : entity->components) {
            component->update(entity);
        }
    }
}

void ECManager::cleanup() {
    for (Entity *entity : this->entities) {
        this->deallocate(entity);
    }
}
