'use strict';

import dispatcher from '../dispatcher';
import EventEmitter from 'events';
import constants from '../constants/Player';
import PlayerActions from '../actions/Player';

const EVENT = 'fromPlayerStore';

let _state = {
  tracks: [],
  currentTrackIndex: -1,
  currentTrack: {
    'duration': undefined,
    'id': undefined,
    'album.cover': undefined,
    'album.title': undefined,
    'artist.name': undefined,
    'title': undefined,
  },
  isPlaying: false,
};

const store = { ...EventEmitter.prototype,
  getState() {
    return _state;
  },

  getTracks() {
    return _state.tracks;
  },

  getCurrentTrack() {
    return _state.currentTrack;
  },

  getPreviousTrackId() {
    return _state.currentTrackIndex > 0 ?
      _state.tracks[_state.currentTrackIndex - 1] : null;
  },

  getNextTrackId() {
    return _state.currentTrackIndex < _state.tracks.length ?
      _state.tracks[_state.currentTrackIndex + 1] : null;
  },

  isPlaying() {
    return _state.isPlaying;
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

      case constants.SET_TRACKS:
        _state.tracks = action.tracks;
        store.emitChange();
        break;

      case constants.SET_CURRENT_TRACK:
        _state.currentTrack = action.track;
        store.emitChange();
        break;

      case constants.SET_CURRENT_TRACK_WITH_INDEX:
        _state.currentTrack = action.track;
        _state.currentTrackIndex = action.index;
        store.emitChange();
        break;

      case constants.PLAY_BACKWARD:
        if (!store.getPreviousTrackId()) break;

        _state.currentTrack = _state.tracks[--_state.currentTrackIndex];
        store.emitChange();
        break;

      case constants.PLAY_FORWARD:
        if (!store.getNextTrackId()) break;

        _state.currentTrack = _state.tracks[++_state.currentTrackIndex];
        store.emitChange();
        break;

      case constants.IS_PLAYING:
        _state.isPlaying = action.value;
        store.emitChange();
        break;
    }
  }),
};

export default store;
