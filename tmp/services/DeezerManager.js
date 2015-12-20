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

class DeezerMock {
  connect() {
    return new Promise((resolve, reject) => {
      setTimeout(function() {
        resolve(true);
      }, 5000);
    });
  }

  isSessionValid(cb) {
    setTimeout(function() {
      cb(false);
    }, 5000);
  }

  playTrack(id) {
    return new Promise((resolve, reject) => {
      setTimeout(function() {
        resolve(true);
      }, 5000);
    });
  }

  async getFavoritesTracks() {
    let response = await fetch('http://api.deezer.com/playlist/69512271');
    let body = await response.json();

    let tracks = body.tracks.data.map((track) => {
      return flatten(track)
    });

    return tracks;
  }

  pause() {
    console.log('pause');
  }

  play() {
    console.log('play');
  }
}

export default new DeezerManager();
// export default new DeezerMock();
