/* @flow */
'use strict';

import React from 'react-native';
import FontAwesomeIcon from 'react-native-vector-icons/FontAwesome';
import IonicIcon from 'react-native-vector-icons/Ionicons';

import Component from './Component';
import PlayerProgressTime from './PlayerProgressTime';
import Cover from './Cover';

const {
  Navigator,
  StyleSheet,
  View,
  Text,
  Image,
} = React;


class PlayerInfo extends Component{

  state = {};

  render() {
    return (
      <View style={styles.container}>
        <View style={styles.row}>
          <Cover
            key={this.props.cover}
            size="large"
            width={182}
            height={182}
            source={`${this.props.cover}?size=big`} />
        </View>

          <View style={styles.trackInfoView}>
            <IonicIcon name="ios-clock-outline" size={20} color="#fff" />
            <View style={styles.trackInfoText}>
              <Text style={styles.title} numberOfLines={1}>{this.props.title}</Text>
              <Text style={styles.formText} numberOfLines={1}>from {this.props.artistName} - {this.props.albumTitle}</Text>
            </View>
            <IonicIcon name="more" size={20} color="#fff" />
          </View>

        <View style={styles.row}>
          <View style={styles.actionsView}>
            <View style={styles.actionDislike}>
              <FontAwesomeIcon name="heart-o" size={22} color="#fff" />
              <View style={styles.actionLine}/>
            </View>
            <View style={styles.actionLike}>
              <FontAwesomeIcon name="heart" size={22} color="#007FE7" />
            </View>
          </View>
        </View>
        <PlayerProgressTime duration={this.props.duration} />
      </View>
    );
  }
};

const actionViewHeight = 62,
  actionViewWidth = actionViewHeight,
  actionViewRadius = actionViewWidth / 2;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingTop: 84,
    paddingHorizontal: 20,
  },

  row: {
    alignItems: 'center',
  },

  headerView: {
    alignItems: 'center',
    marginBottom: 20,
  },

  typeTitle: {
    color: '#d2d2d7',

    fontSize: 10,
    letterSpacing: 2,
    paddingBottom: 2,
  },

  playlistTitle: {
    color: '#fff',

    fontSize: 18,
    fontWeight: '500',
  },

  cover: {
    width: 182,
    height: 182,
  },

  trackInfoView: {
    alignItems: 'center',
    flexDirection: 'row',
    paddingTop: 10,
  },

  trackInfoText: {
    marginHorizontal: 12,
    alignItems: 'center',
    width: 0,
    flex: 1,
  },

  title: {
    color: '#F6F5F6',
    fontSize: 17,
    fontWeight: '600',
    paddingBottom: 5,
    maxWidth: 100,

  },

  formText: {
    color: '#F6F5F6',
    fontWeight: '500',
    fontSize: 12,
    fontStyle: 'italic',
    maxWidth: 100,

  },

  actionsView: {
    flexDirection: 'row',
    marginTop: 17,
  },

  actionLike: {
    height: actionViewHeight,
    width: actionViewWidth,
    borderRadius: actionViewRadius,
    alignItems: 'center',
    justifyContent: 'center',
    borderWidth: 2,
    borderColor: 'rgba(255,255,255,0.3)',
  },

  actionDislike: {
    height: actionViewHeight,
    width: actionViewWidth,
    borderRadius: actionViewRadius,
    alignItems: 'center',
    justifyContent: 'center',
    borderWidth: 2,
    borderColor: 'rgba(255,255,255,0.3)',

    marginRight: 26,
  },

  actionLine: {
    width: 2,
    height: actionViewHeight - 3,
    backgroundColor: 'rgba(255,255,255,0.3)',

    position: 'absolute',
    top: 0,
    left: actionViewWidth / 2 - 3,
    transform: [
      { rotate: '-45deg' }
    ]
  },

});

export default PlayerInfo;
