'use strict';

import dispatcher from '../dispatcher';
import EventEmitter from 'events';
import assign from 'object-assign';
import constants from '../constants/App';

const EVENT = 'fromApplicationStore';

let _state = {
  isPlayerVisible: false,
};

const store = { ...EventEmitter.prototype,
  getState() {
    return _state;
  },

  getPlayerVisbleStatus() {
    return _state.isPlayerVisible;
  },


  emitChange() {
    this.emit(EVENT);
  },

  addChangeListener(callback) {
    this.on(EVENT, callback);
  },

  removeChangeListener(callback) {
    this.removeListener(EVENT, callback);
  },


  dispatchToken: dispatcher.register((action) => {
    switch(action.actionType) {

      case constants.SET_PLAYER_VISIBLE_STATUS:
        _state.isPlayerVisible = action.value;
        store.emitChange();
        break;
    }
  }),
};

export default store;
