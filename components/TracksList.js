/* @flow */
'use strict';

import React from 'react-native';

import Item from './TracksItem';
import Component from './Component';

import PlayerStore from '../stores/Player';
import PlayerActions from '../actions/Player';
import AppActions from '../actions/App';

const {
  StyleSheet,
  View,
  ScrollView,
} = React;

class TracksList extends Component {

  state = {};

  componentWillMount() {
    this.playTrackWithId = this.playTrackWithId.bind(this);
    this.playTrackWithIndex = this.playTrackWithIndex.bind(this);
    this._onChange = this._onChange.bind(this);
    this._setupState();
  }

  componentDidMount() {
    PlayerStore.addChangeListener(this._onChange);
  }

  componentWillUnmount() {
    PlayerStore.removeChangeListener(this._onChange);
  }

  _setupState() {
    let { currentTrack, tracks } = PlayerStore.getState();
    this.setState({ currentTrack, tracks });
  }

  _onChange() {
    this._setupState();
  }

  playTrackWithId(id) {
    let currentTrack = this.state.tracks.find(item => item.id === id);
    if (this.state.currentTrack !== currentTrack) {
      PlayerActions.setCurrentTrack(currentTrack);
    }
    AppActions.setPlayerVisibleStatus(true);
  }

  playTrackWithIndex(index) {
    let currentTrack = this.state.tracks[index];
    if (this.state.currentTrack !== currentTrack) {
      PlayerActions.setCurrentTrackWithIndex(currentTrack, index);
    }
    AppActions.setPlayerVisibleStatus(true);
  }

  renderItems(track, index) {
    let { id } = track;

    return (
      <Item
        playTrackWithIndex={this.playTrackWithIndex}
        playTrackWithId={this.playTrackWithId}

        isNowPlaying={this.state.currentTrack.id === id}
        key={id}
        index={index}
        {...track} />
    );
  }

  render() {
    return (
      <ScrollView style={styles.container}>
        {this.state.tracks.map(this.renderItems, this)}
      </ScrollView>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    padding: 8,
    paddingTop: 4,
  }
});

export default TracksList;
