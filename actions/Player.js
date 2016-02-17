'use strict';

import dispatcher from '../dispatcher';
import constants from '../constants/Player';
import PlayerStore from '../stores/Player';

import DeezerManager from '../services/DeezerManager';

const actions = {
  setTracks(tracks) {
    dispatcher.dispatch({
      actionType: constants.SET_TRACKS,
      tracks
    });
  },

  setCurrentTrack(track) {
    dispatcher.dispatch({
      actionType: constants.SET_CURRENT_TRACK,
      track
    });
    actions._playTrack(track.id);
  },

  setCurrentTrackWithIndex(track, index) {
    dispatcher.dispatch({
      actionType: constants.SET_CURRENT_TRACK_WITH_INDEX,
      track,
      index
    });
    actions._playTrack(track.id);
  },

  async _playTrack(id) {
    let value = await DeezerManager.playTrack(id);
    actions.changePlayerStatus(value);
  },

  playBackward() {
    let track = PlayerStore.getPreviousTrackId();

    dispatcher.dispatch({
      actionType: constants.PLAY_BACKWARD,
    });

    track && actions._playTrack(track.id);
  },

  playForward() {
    let track = PlayerStore.getNextTrackId();

    dispatcher.dispatch({
      actionType: constants.PLAY_FORWARD,
    });

    track && actions._playTrack(track.id);
  },

  pause() {
    this.changePlayerStatus(false);
    DeezerManager.pause();
  },

  play() {
    this.changePlayerStatus(true);
    DeezerManager.play()
  },

  changePlayerStatus(value) {
    dispatcher.dispatch({
      actionType: constants.IS_PLAYING,
      value
    });
  }
};

export default actions;
