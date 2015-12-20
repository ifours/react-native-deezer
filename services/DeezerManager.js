'use strict';

import React from 'react-native';
import flatten from 'flat';

const { NativeModules: { DeezerManager: DeezerRNManager } } = React

class DeezerManager {
  connect() {
    return new Promise((resolve, reject) => {
      DeezerRNManager.connect((decision) => {
        decision ? resolve(decision) : reject(decision);
      });
    });
  }

  checkSession(cb) {
    DeezerRNManager.isSessionValid(cb);
  }

  async playTrack(id) {
    return await DeezerRNManager.playTrack(id);
  }

  async getPlaylistTracks(id) {
    return await DeezerRNManager.getPlaylistTracks(id);
  }

  async getFavoritesTracks() {
    return await DeezerRNManager.getFavoritesTracks();
  }

  async getPlaylists() {
    return await DeezerRNManager.getPlaylists();
  }

  pause() {
    DeezerRNManager.pause();
  }

  play() {
    DeezerRNManager.play();
  }
}

export default new DeezerManager();
