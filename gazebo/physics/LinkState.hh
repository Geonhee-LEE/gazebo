/*
 * Copyright (C) 2012-2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef GAZEBO_PHYSICS_LINKSTATE_HH_
#define GAZEBO_PHYSICS_LINKSTATE_HH_

#include <vector>
#include <string>

#include <sdf/sdf.hh>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Pose3.hh>

#include "gazebo/physics/State.hh"
#include "gazebo/physics/CollisionState.hh"
#include "gazebo/math/Pose.hh"
#include "gazebo/util/system.hh"

namespace gazebo
{
  namespace physics
  {
    /// \addtogroup gazebo_physics
    /// \{

    /// \class LinkState LinkState.hh physics/physics.hh
    /// \brief Store state information of a physics::Link object
    ///
    /// This class captures the entire state of a Link at one
    /// specific time during a simulation run.
    ///
    /// State of a Link includes the state of itself all its child Collision
    /// entities.
    class GZ_PHYSICS_VISIBLE LinkState : public State
    {
      /// \brief Default constructor
      public: LinkState();

      /// \brief Constructor
      ///
      /// Build a LinkState from an existing Link.
      /// \param[in] _model Pointer to the Link from which to gather state
      /// info.
      /// \param[in] _realTime Real time stamp.
      /// \param[in] _simTime Sim time stamp
      /// \param[in] _iterations Simulation iterations.
      public: LinkState(const LinkPtr _link, const common::Time &_realTime,
                  const common::Time &_simTime, const uint64_t _iterations);

      /// \brief Constructor
      ///
      /// Build a LinkState from an existing Link.
      /// \param[in] _model Pointer to the Link from which to gather state
      /// info.
      public: explicit LinkState(const LinkPtr _link);

      /// \brief Constructor
      ///
      /// Build a LinkState from SDF data
      /// \param[in] _sdf SDF data to load a link state from.
      public: explicit LinkState(const sdf::ElementPtr _sdf);

      /// \brief Destructor.
      public: virtual ~LinkState();

      /// \brief Load a LinkState from a Link pointer.
      ///
      /// Build a LinkState from an existing Link.
      /// \param[in] _model Pointer to the Link from which to gather state
      /// info.
      /// \param[in] _realTime Real time stamp.
      /// \param[in] _simTime Sim time stamp.
      /// \param[in] _iterations Simulation iterations.
      public: void Load(const LinkPtr _link, const common::Time &_realTime,
                  const common::Time &_simTime, const uint64_t _iterations);

      /// \brief Load state from SDF element.
      ///
      /// Load LinkState information from stored data in and SDF::Element.
      /// \param[in] _elem Pointer to the SDF::Element containing state info.
      public: virtual void Load(const sdf::ElementPtr _elem);

      /// \brief Get the link pose.
      /// \return The math::Pose of the Link.
      /// \deprecated See const ignition::math::Pose3d Pose() const
      public: math::Pose GetPose() const GAZEBO_DEPRECATED(8.0);

      /// \brief Get the link pose.
      /// \return The math::Pose of the Link.
      public: const ignition::math::Pose3d &Pose() const;

      /// \brief Get the link velocity.
      /// \return The velocity represented as a math::Pose.
      /// \deprecated See const ignition::math::Pose3d Velocity() const
      public: math::Pose GetVelocity() const GAZEBO_DEPRECATED(8.0);

      /// \brief Get the link velocity.
      /// \return The velocity represented as a math::Pose.
      public: const ignition::math::Pose3d &Velocity() const;

      /// \brief Get the link acceleration.
      /// \return The acceleration represented as a math::Pose.
      /// \deprecated See const ignition::math::Pose3d Acceleration() const
      public: math::Pose GetAcceleration() const GAZEBO_DEPRECATED(8.0);

      /// \brief Get the link acceleration.
      /// \return The acceleration represented as a math::Pose.
      public: const ignition::math::Pose3d &Acceleration() const;

      /// \brief Get the force applied to the Link.
      /// \return Magnitude of the force.
      /// \deprecated See const ignition::math::Pose3d &Wrench() const
      public: math::Pose GetWrench() const GAZEBO_DEPRECATED(8.0);

      /// \brief Get the force applied to the Link.
      /// \return Magnitude of the force.
      public: const ignition::math::Pose3d &Wrench() const;

      /// \brief Get the number of link states.
      ///
      /// This returns the number of Collisions recorded.
      /// \return Number of CollisionState recorded.
      /// \deprecated See unsigned int CollisionStateCount() const
      public: unsigned int GetCollisionStateCount() const
              GAZEBO_DEPRECATED(8.0);

      /// \brief Get the number of link states.
      ///
      /// This returns the number of Collisions recorded.
      /// \return Number of CollisionState recorded.
      public: unsigned int CollisionStateCount() const;

      /// \brief Get a collision state.
      ///
      /// Get a Collision State based on an index, where index is in the
      /// range of  0...LinkState::CollisionStateCount.
      /// \param[in] _index Index of the CollisionState.
      /// \return State of the Collision.
      /// \deprecated See CollisionState CollisionStateByIndex(
      /// const unsigned int _index) const
      public: CollisionState GetCollisionState(unsigned int _index) const
              GAZEBO_DEPRECATED(8.0);

      /// \brief Get a collision state.
      ///
      /// Get a Collision State based on an index, where index is in the
      /// range of  0...LinkState::CollisionStateCount.
      /// \param[in] _index Index of the CollisionState.
      /// \return State of the Collision.
      public: CollisionState CollisionStateByIndex(
                  const unsigned int _index) const;

      /// \brief Get a link state by link name.
      ///
      /// Searches through all CollisionStates.
      /// Returns the CollisionState with the matching name, if any.
      /// \param[in] _collisionName Name of the CollisionState
      /// \return State of the Collision.
      /// \deprecated See CollisionState CollisionStateByName(
      ///            const std::string &_collisionName) const
      public: CollisionState GetCollisionState(
                  const std::string &_collisionName) const
              GAZEBO_DEPRECATED(8.0);

      /// \brief Get a collision state by collision name.
      ///
      /// Searches through all CollisionStates.
      /// Returns the CollisionState with the matching name, if any.
      /// \param[in] _collisionName Name of the CollisionState
      /// \return State of the Collision.
      public: CollisionState CollisionStateByName(
                  const std::string &_collisionName) const;

      /// \brief Get the collision states.
      /// \return A vector of collision states.
      /// \deprecated See const std::vector<CollisionState> &
      /// GetCollisionStates() const
      public: const std::vector<CollisionState> &GetCollisionStates() const
              GAZEBO_DEPRECATED(8.0);

      /// \brief Get the collision states.
      /// \return A vector of collision states.
      public: const std::vector<CollisionState> &CollisionStates() const;

      /// \brief Return true if the values in the state are zero.
      /// \return True if the values in the state are zero.
      public: bool IsZero() const;

      /// \brief Populate a state SDF element with data from the object.
      /// \param[out] _sdf SDF element to populate.
      public: void FillSDF(sdf::ElementPtr _sdf);

      /// \brief Set the wall time when this state was generated
      /// \param[in] _time The absolute clock time when the State
      /// data was recorded.
      public: virtual void SetWallTime(const common::Time &_time);

      /// \brief Set the real time when this state was generated
      /// \param[in] _time Clock time since simulation was stated.
      public: virtual void SetRealTime(const common::Time &_time);

      /// \brief Set the sim time when this state was generated
      /// \param[in] _time Simulation time when the data was recorded.
      public: virtual void SetSimTime(const common::Time &_time);

      /// \brief Set the simulation iterations when this state was generated
      /// \param[in] _iterations Simulation iterations when the data was
      /// recorded.
      public: virtual void SetIterations(const uint64_t _iterations);

      /// \brief Assignment operator
      /// \param[in] _state State value
      /// \return this
      public: LinkState &operator=(const LinkState &_state);

      /// \brief Subtraction operator.
      /// \param[in] _pt A state to substract.
      /// \return The resulting state.
      public: LinkState operator-(const LinkState &_state) const;

      /// \brief Addition operator.
      /// \param[in] _pt A state to add.
      /// \return The resulting state.
      public: LinkState operator+(const LinkState &_state) const;

      /// \brief Stream insertion operator
      /// \param[in] _out output stream
      /// \param[in] _state Link state to output
      /// \return the stream
      public: inline friend std::ostream &operator<<(std::ostream &_out,
                  const gazebo::physics::LinkState &_state)
      {
        ignition::math::Vector3d q(_state.pose.Rot().Euler());

        _out << std::fixed << std::setprecision(5)
          << "<link name='" << _state.name << "'>"
          << "<pose>"
          << _state.pose.Pos().X() << " "
          << _state.pose.Pos().Y() << " "
          << _state.pose.Pos().Z() << " "
          << q.X() << " "
          << q.Y() << " "
          << q.Z() << " "
          << "</pose>";

        /// Disabling this for efficiency.
        q = _state.velocity.Rot().Euler();

         _out << std::fixed << std::setprecision(4)
           << "<velocity>"
           << _state.velocity.Pos().X() << " "
           << _state.velocity.Pos().Y() << " "
           << _state.velocity.Pos().Z() << " "
           << q.X() << " "
           << q.Y() << " "
           << q.Z() << " "
           << "</velocity>";
        // << "<acceleration>" << _state.acceleration << "</acceleration>"
        // << "<wrench>" << _state.wrench << "</wrench>";

        /// Disabling this for efficiency.
        // for (std::vector<CollisionState>::const_iterator iter =
        //      _state.collisionStates.begin();
        //      iter != _state.collisionStates.end(); ++iter)
        // {
        //   _out << *iter;
        // }

        _out << "</link>";

        return _out;
      }

      /// \brief 3D pose of the link relative to the model.
      private: ignition::math::Pose3d pose;

      /// \brief Velocity of the link (linear and angular).
      private: ignition::math::Pose3d velocity;

      /// \brief Acceleration of the link (linear and angular).
      private: ignition::math::Pose3d acceleration;

      /// \brief Force on the link(linear and angular).
      private: ignition::math::Pose3d wrench;

      /// \brief State of all the child Collision objects.
      private: std::vector<CollisionState> collisionStates;
    };
    /// \}
  }
}
#endif
