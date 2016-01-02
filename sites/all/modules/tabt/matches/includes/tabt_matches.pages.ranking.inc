<?php

/**
 * @file
 * Create and theme the rankingpage.
 */

/**
 * Create the rankingpage for a team.

 * This page can be formatted with theme_tabt_ranking().
 * The rankingarray can be accessed through $ranking.

 *
*@param $id
 *   The team to get the ranking for.
 * @param season
 *   The season being viewed.
 */
function tabt_matches_ranking($id, $season = NULL) {
  if ((variable_get('tabt_linked_to_club', 'linked') == 'unlinked')) {
    // If no club is linked, $id should indicate a division.

    $rankingResult = tabt_matches_get_ranking($id);
    if (!$rankingResult) {
      // Invalid division ID.
      drupal_not_found();
      return;
    }

    $title = format_string(variable_get('tabt_matches_rankingpage_title',
      'Ranking @division'), array(
      '@division' => $rankingResult->DivisionName,
    ));
    drupal_set_title($title);

    $teaminfo = null;
    $season = null;
  }
  else {
    // If a club is linked, $id should indicate a valid team.

    // We only show the ranking for a valid team.
    if (!tabt_is_valid_team(drupal_strtoupper($id), $season)) {
      drupal_not_found();
      return;
    }

    // Get the teaminfo so we can get the division.
    $teaminfo = tabt_get_teaminfo($id, $season);

    if (!$teaminfo) {
      // If we get here, the API screwed up and we didn't get a valid
      // TeamEntry-object.
      drupal_not_found();
      return;
    }
    $season = tabt_process_seasonnumber($season);
    // Set the pagetitle and replace the tokens.
    $rankingResult = tabt_matches_get_ranking($teaminfo->DivisionId);

    $title = format_string(variable_get('tabt_matches_rankingpage_title',
      'Ranking @club @team: @division - @season'), array(
      '@club' => variable_get('tabt_club_name', 'Team'),
      '@team' => tabt_get_teamname($id, $season),
      '@division' => $rankingResult->DivisionName,
      '@season' => tabt_get_seasonname($season)
    ));
    drupal_set_title($title);

  }

    // Get the ranking.


  return array(
      '#theme'     => 'tabt_ranking',
      'team'       => $id,
      'ranking'    => $rankingResult->Ranking,
      '#teaminfo'  => $teaminfo,
      '#ranking'   => $rankingResult->Ranking,
      '#season' => $season
  );
}
