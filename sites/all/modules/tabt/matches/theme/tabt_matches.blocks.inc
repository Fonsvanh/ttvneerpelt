<?php

/**
 * @file
 * Theme the blocks.
 */

/**
 * Theme the list of upcoming matches.
 */
function theme_tabt_upcoming_matches($variables) {
  if (variable_get('tabt_locale')) {
    setlocale(LC_TIME, variable_get('tabt_locale'));
  }

  $matches = $variables['matches'];

  $header = array(t('Date'), t('Home'), t('Away', array(), array('context' => 'game')));
  $rows = array();

  // Check for Windows replace the %e modifier correctly
  if (strtoupper(substr(PHP_OS, 0, 3)) == 'WIN') {
    $date_format_string = '%a %#d/%b, %Hu%M';
  }
  else {
    $date_format_string = '%a %e/%b, %Hu%M';
  }

  foreach ($matches as $team => $match) {
    if (isset($match->AwayTeam)) {
      $date = DateTime::createFromFormat('Y-m-d H:i:s', $match->Date . ' ' . $match->Time);
      if ($date) {
        $date_string = strftime($date_format_string, $date->getTimestamp());
      }
      else {
        $date_string = '';
      }
      $row = array($date_string);
      $match->HomeTeam = check_plain($match->HomeTeam);
      $match->AwayTeam = check_plain($match->AwayTeam);
      $teaminfo = tabt_get_teaminfo($team);
      if ($match->isHome && drupal_strtoupper(drupal_substr($match->HomeTeam, -1)) == drupal_strtoupper($teaminfo->Team)) {
        $match->HomeTeam = array(
          'style' => 'font-weight: bold;',
          'data' => l($match->HomeTeam, variable_get('tabt_matches_matchespage', 'championship/calendar') . '/' . tabt_get_teamurl($team))
        );
      }
      else {
        $match->AwayTeam = array(
          'style' => 'font-weight: bold;',
          'data' => l($match->AwayTeam, variable_get('tabt_matches_matchespage', 'championship/calendar') . '/' . tabt_get_teamurl($team))
        );
      }
      array_push($row, $match->HomeTeam, $match->AwayTeam);
      $rows[] = $row;
    }
    else {
      $rows[] = array(
        '',
        array(
          'style' => 'font-weight: bold;',
          'data' => l(tabt_get_teamname($team), variable_get('tabt_matches_matchespage', 'championship/calendar') . '/' . tabt_get_teamurl($team))
        ),
        ''
      );
    }
  }
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No matches scheduled.')));

}

/**
 * Theme the list of past matches.
 */
function theme_tabt_past_matches($variables) {
  if (variable_get('tabt_locale')) {
    setlocale(LC_TIME, variable_get('tabt_locale'));
  }

  $matches = $variables['matches'];

  $header = array(t('Date'), t('Home'), t('Away', array(), array('context' => 'game')), t('Score'));
  $rows = array();

  // Check for Windows replace the %e modifier correctly
  if (strtoupper(substr(PHP_OS, 0, 3)) == 'WIN') {
    $date_format_string = '%a %#d/%b';
  }
  else {
    $date_format_string = '%a %e/%b';
  }

  foreach ($matches as $team => $match) {
    if (isset($match->AwayTeam)) {
      $date = DateTime::createFromFormat('Y-m-d H:i:s', $match->Date . ' ' . $match->Time);
      if ($date) {

        $date_string = strftime($date_format_string, $date->getTimestamp());
      }
      else {
        $date_string = '';
      }
      $row = array($date_string);
      $home_style = '';
      $away_style = '';
      if ($match->Withdrawal == 0 || $match->Withdrawal == 2) {
        $home_style = 'text-decoration: line-through; ';
      }
      elseif ($match->Withdrawal == 1 || $match->Withdrawal == 2) {
        $away_style = 'text-decoration: line-through; ';
      }
      $match->HomeTeam = check_plain($match->HomeTeam);
      $match->AwayTeam = check_plain($match->AwayTeam);
      $teaminfo = tabt_get_teaminfo($team);
      if ($match->isHome && drupal_strtoupper(drupal_substr($match->HomeTeam, -1)) == drupal_strtoupper($teaminfo->Team)) {
        $match->HomeTeam = array(
          'style' => $home_style . 'font-weight: bold;',
          'data' => l($match->HomeTeam, variable_get('tabt_matches_rankingpage', 'championship/calendar') . '/' . tabt_get_teamurl($team))
        );
      }
      else {
        $match->AwayTeam = array(
          'style' => $away_style . 'font-weight: bold;',
          'data' => l($match->AwayTeam, variable_get('tabt_matches_rankingpage', 'championship/calendar') . '/' . tabt_get_teamurl($team))
        );
      }
      if (isset($match->Link)) {
        $match->Score = l($match->Score, $match->Link);
      }
      elseif (!isset($match->Score)) {
        $match->Score = '';
      }
      array_push($row, $match->HomeTeam, $match->AwayTeam, $match->Score);
      $rows[] = $row;
    }
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No matches played.')));
}