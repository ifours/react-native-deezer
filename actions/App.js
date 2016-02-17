'use strict';

import dispatcher from '../dispatcher';
import AppConstants from '../constants/App';

const actions = {
  setPlayerVisibleStatus(value) {
    dispatcher.dispatch({
      actionType: AppConstants.SET_PLAYER_VISIBLE_STATUS,
      value: value,
    });
  },
};

export default actions;
