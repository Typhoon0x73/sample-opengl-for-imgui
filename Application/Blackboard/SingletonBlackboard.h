#ifndef SINGLETONBLACKBOARD_H_
#define SINGLETONBLACKBOARD_H_

#include "Blackboard.h"
#include "../../Framework/Common/Singleton.h"

template < typename... Types >
class SingletonBlackboard : public Sample::Singleton<Blackboard<Types...>>
{
    friend class Sample::Singleton<Blackboard<Types...>>;
};

#define g_pGetBlackboard(x)    SingletonBlackboard< x >::GetInstance().get< x >()
#define g_BlackboardRelease(x) SingletonBlackboard< x >::Release()

#endif // !SINGLETONBLACKBOARD_H_
