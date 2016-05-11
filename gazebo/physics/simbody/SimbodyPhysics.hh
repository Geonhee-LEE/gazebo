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
#ifndef GAZEBO_PHYSICS_SIMBODY_SIMBODYPHYSICS_HH
#define GAZEBO_PHYSICS_SIMBODY_SIMBODYPHYSICS_HH

#include <string>

#include <ignition/math/Vector3.hh>
#include <ignition/math/Quaternion.hh>

#include "gazebo/physics/PhysicsEngine.hh"
#include "gazebo/physics/Collision.hh"
#include "gazebo/physics/Shape.hh"
#include "gazebo/physics/simbody/SimbodyTypes.hh"

#include "gazebo/physics/simbody/simbody_inc.h"
#include "gazebo/util/system.hh"

namespace gazebo
{
  namespace physics
  {
    // Forward declare private data
    class SimbodyPhysicsPrivate;

    /// \ingroup gazebo_physics
    /// \addtogroup gazebo_physics_simbody Simbody Physics
    /// \{

    /// \brief Simbody physics engine
    class GZ_PHYSICS_VISIBLE SimbodyPhysics : public PhysicsEngine
    {
      /// \brief Constructor
      public: SimbodyPhysics(WorldPtr _world);

      /// \brief Destructor
      public: virtual ~SimbodyPhysics();

      // Documentation inherited
      public: virtual void Load(sdf::ElementPtr _sdf);

      // Documentation inherited
      public: virtual void Init();

      // Documentation inherited
      public: virtual void Reset();

      /// \brief Add a Model to the Simbody system.
      /// \param[in] _model Pointer to the model to add into Simbody.
      public: void InitModel(const physics::ModelPtr _model);

      // Documentation inherited
      public: virtual void InitForThread();

      // Documentation inherited
      public: virtual void UpdateCollision();

      // Documentation inherited
      public: virtual void UpdatePhysics();

      // Documentation inherited
      public: virtual void Fini();

      // Documentation inherited
      public: virtual std::string Type() const;

      // Documentation inherited
      public: virtual LinkPtr CreateLink(ModelPtr _parent);

      // Documentation inherited
      public: virtual CollisionPtr CreateCollision(const std::string &_type,
                                                   LinkPtr _body);

      // Documentation inherited
      public: virtual JointPtr CreateJoint(const std::string &_type,
                                           ModelPtr _parent);

      // Documentation inherited
      public: virtual ShapePtr CreateShape(const std::string &_shapeType,
                                           CollisionPtr _collision);

      /// \brief Register a joint with the dynamics world
      public: SimTK::MultibodySystem *DynamicsWorld() const;

      // Documentation inherited
      public: virtual void SetGravity(const ignition::math::Vector3d &_gravity);

      // Documentation inherited
      public: virtual void DebugPrint() const;

      // Documentation inherited
      public: virtual void SetSeed(const uint32_t _seed);

      // Documentation inherited
      public: virtual ModelPtr CreateModel(BasePtr _parent);

      /// \brief Convert gazebo::math::Quaternion to SimTK::Quaternion
      /// \param[in] _q Gazebo's math::Quaternion object
      /// \return Simbody's SimTK::Quaternion object
      public: static SimTK::Quaternion QuadToQuad(const math::Quaternion &_q)
              GAZEBO_DEPRECATED(8.0);

      /// \brief Convert ignition::math::Quaterniond to SimTK::Quaternion
      /// \param[in] _q ignition::math::Quaterniond object
      /// \return Simbody's SimTK::Quaternion object
      public: static SimTK::Quaternion QuadToQuad(
                  const ignition::math::Quaterniond &_q);

      /// \brief Convert SimTK::Quaternion to gazebo::math::Quaternion
      /// \param[in] _q Simbody's SimTK::Quaternion object
      /// \return Gazeb's math::Quaternion object
      public: static math::Quaternion QuadToQuad(const SimTK::Quaternion &_q)
              GAZEBO_DEPRECATED(8.0);

      /// \brief Convert gazebo::math::Vector3 to SimTK::Vec3
      /// \param[in] _v Gazebo's math::Vector3 object
      /// \return Simbody's SimTK::Vec3 object
      public: static SimTK::Vec3 Vector3ToVec3(const math::Vector3 &_v)
              GAZEBO_DEPRECATED(8.0);

      /// \brief Convert ignition::math::Vector3d to SimTK::Vec3
      /// \param[in] _v ignition::math::Vector3d object
      /// \return Simbody's SimTK::Vec3 object
      public: static SimTK::Vec3 Vector3ToVec3(
                  const ignition::math::Vector3d &_v);

      /// \brief Convert SimTK::Vec3 to gazebo::math::Vector3
      /// \param[in] _v Simbody's SimTK::Vec3 object
      /// \return Gazeb's math::Vector3 object
      public: static math::Vector3 Vec3ToVector3(const SimTK::Vec3 &_v)
              GAZEBO_DEPRECATED(8.0);

      /// \brief Convert SimTK::Vec3 to ignition::math::Vector3d
      /// \param[in] _v Simbody's SimTK::Vec3 object
      /// \return ignition::math::Vector3d object
      public: static ignition::math::Vector3d Vec3ToVector3Ign(
                  const SimTK::Vec3 &_v);

      /// \brief Convert the given pose in x,y,z,thetax,thetay,thetaz format to
      /// a Simbody Transform. The rotation angles are interpreted as a
      /// body-fixed sequence, meaning we rotation about x, then about
      /// the new y, then about the now twice-rotated z.
      /// \param[in] _pose Gazeb's math::Pose object
      /// \return Simbody's SimTK::Transform object
      public: static SimTK::Transform Pose2Transform(const math::Pose &_pose)
              GAZEBO_DEPRECATED(8.0);

      /// \brief Convert the given pose in x,y,z,thetax,thetay,thetaz format to
      /// a Simbody Transform. The rotation angles are interpreted as a
      /// body-fixed sequence, meaning we rotation about x, then about
      /// the new y, then about the now twice-rotated z.
      /// \param[in] _pose ignition::math::Pose3d object
      /// \return Simbody's SimTK::Transform object
      public: static SimTK::Transform Pose2Transform(
                  const ignition::math::Pose3d &_pose);

      /// \brief Convert a Simbody transform to a pose in x,y,z,
      /// thetax,thetay,thetaz format.
      /// \param[in] _xAB Simbody's SimTK::Transform object
      /// \return Gazeb's math::Pose object
      public: static math::Pose Transform2Pose(const SimTK::Transform &_xAB)
              GAZEBO_DEPRECATED(8.0);

      /// \brief Convert a Simbody transform to a pose in x,y,z,
      /// thetax,thetay,thetaz format.
      /// \param[in] _xAB Simbody's SimTK::Transform object
      /// \return ignition::math::Pose3d object
      public: static ignition::math::Pose3d Transform2PoseIgn(
                  const SimTK::Transform &_xAB);

      /// \brief If the given element contains a <pose> element, return it as a
      /// Transform. Otherwise return the identity Transform. If there
      /// is more than one <pose> element, only the first one is processed.
      public: static SimTK::Transform Pose(sdf::ElementPtr _element);

      /// \brief Convert Base::Type() to string,
      /// this is needed by the MultibodyGraphMaker.
      /// \param[in] _type Joint type returned by Joint::Type().
      /// \return a hard-coded string needed by the MultibodyGraphMaker.
      public: static std::string TypeString(const unsigned int _type);

      /// \brief Convert Base::Type() to string,
      /// this is needed by the MultibodyGraphMaker.
      /// \param[in] _type Joint type returned by Joint::Type().
      /// \return a hard-coded string needed by the MultibodyGraphMaker.
      public: static std::string TypeString(
                  const physics::Base::EntityType _type);

      /// \brief Get a reference to the simtk multibody system
      /// \return Reference to the simtk multibody system
      public: SimTK::MultibodySystem &System() const;

      /// \brief Get a reference to the simtk discrete forces
      /// \return Reference to the simtk  discrete forces
      public: SimTK::Force::DiscreteForces &DiscreteForces() const;

      /// \brief Get a pointer to the simtk integrator
      /// \return Pointer to the simtk integrator
      public: SimTK::Integrator *Integ() const;

      /// \brief Return if the physics engine has been initialized.
      /// \return True if initialized.
      public: bool PhysicsInitialized() const;

      /// \brief Return simbody physics stepped flag.
      /// \return True if physics is stepped.
      public: bool PhysicsStepped() const;

      // Documentation inherited
      public: virtual boost::any Param(const std::string &_key) const;

      // Documentation inherited
      public: virtual bool Param(const std::string &_key,
                  boost::any &_value) const;

      // Documentation inherited
      public: virtual bool SetParam(const std::string &_key,
                  const boost::any &_value);

      /// \brief Get a reference to a simbody gravity object.
      /// \return Reference to a simbody gravity object.
      public: SimTK::Force::Gravity &SimbodyGravity() const;

      // Documentation inherited
      protected: virtual void OnRequest(ConstRequestPtr &_msg);

      // Documentation inherited
      protected: virtual void OnPhysicsMsg(ConstPhysicsPtr &_msg);

      /// \brief CREATE MULTIBODY GRAPH
      /// Define Gazebo joint types, then use links and joints in the
      /// given model to construct a reasonable spanning-tree-plus-constraints
      /// multibody graph to represent that model. An exception will be
      /// thrown if this fails.  Note that this step is not Simbody dependent.
      /// \param[in] _mbgraph Create a MultibodyGraphMaker that is equivalent
      /// of incoming physics::Model.
      /// \param[in] _model Model loaded by Gazebo parsing SDF.
      private: void CreateMultibodyGraph(
        SimTK::MultibodyGraphMaker &_mbgraph, const physics::ModelPtr _model);

      /// \brief BUILD SIMBODY SYSTEM
      /// Given a desired multibody graph, gravity, and the Gazebo model
      /// that was used to generate the graph, create a Simbody System
      /// for it. There are many limitations here, especially in the
      /// handling of contact. Any Gazebo features that we haven't
      /// modeled are just ignored.  The GazeboModel is updated so that
      /// its links and joints have references to their corresponding
      /// Simbody elements.  We set up some visualization here so we
      /// can see what's happening but this would not be needed in Gazebo
      /// since it does its own visualization.
      private: void InitSimbodySystem();

      /// \brief Add a static Model to simbody system, and reinitialize state
      /// \param[in] _model the incoming static Gazebo physics::Model.
      private: void AddStaticModelToSimbodySystem(
                   const physics::ModelPtr _model);

      /// \brief Read from MultibodydGraphMaker and construct a physics::Model.
      /// \param[in] _mbgraph Contain MultibodyGraphMaker object.
      /// \param[in] _model Pointer to gazebo model, not used at this time.
      private: void AddDynamicModelToSimbodySystem(
                   const SimTK::MultibodyGraphMaker &_mbgraph,
                   const physics::ModelPtr _model);

      /// \brief helper function for building SimbodySystem
      private: void AddCollisionsToLink(const physics::SimbodyLink *_link,
        SimTK::MobilizedBody &_mobod, SimTK::ContactCliqueId _modelClique);

      /// \internal
      /// \brief Private data pointer
      private: SimbodyPhysicsPrivate *simbodyPhysicsDPtr;
    };
  /// \}
  }
}
#endif
