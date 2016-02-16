'use strict';

import React from 'react-native';
import flatten, { unflatten } from 'flat';

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
    let tracks = await DeezerRNManager.getPlaylistTracks(id);
    return tracks.map(track => unflatten(track));
  }

  async getFavoritesTracks() {
    let tracks = await DeezerRNManager.getFavoritesTracks();
    return tracks.map(track => unflatten(track));
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
